#include <core/projectmanager.hpp>






ProjectManager::ProjectManager(QObject *parent) : QObject(parent),
    m_loaded_semaphore(0)
{


    /**
     *Set the name of the QObject
     */
    setObjectName("ProjectManager");


}




void ProjectManager::LoadProject()
{




    /**
    *In order to initiate a reload we first need to know if all assets are
    *loaded to avoid crashing worker thread
    */
    if (!parent()->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "ProjectManager: Had to check if all assets are loaded, but could not find the AssetLoader";
        return;
    }



    /**
    *If there is an asset loaded go ahead and perform the SanityCheck - check
    *if all assets are loaded
    */
    if(!parent()->findChild<AssetLoader*>("AssetLoader")->SanityCheck())
    {

        qDebug() << "ProjectManager: Assets are not all loaded successfully, so it's dangerous to reload, aborted!";
        return;

    }




    /**
    *If everything went well untill this point we need to read config.json in
    *order to know which project to load
    */
    m_config_json = aae::Json::GetJsonFromFile("data/config.json");



    /**
     *Before reloading, unload current project
     */
    UnloadProject();





    if (!parent()->findChild<ScriptEngine*>("ScriptEngine"))
    {
        qDebug() << "ProjectManager: Could not find the ScriptEngine!";
        return;
    }



    /**
     *Get the ScriptEngine to load the project
     */
    ScriptEngine * script_engine = parent()->findChild<ScriptEngine*>("ScriptEngine");
    /**
     *Try to load the project specified in the config.json
     */
    SetProjectLoaded(script_engine->LoadProject(m_config_json.toVariant().toMap()["AaetherEngine"].toMap()["project"].toString()));




    /**
    *Check if the project loading went well, if not, abort and issue an error
    */
    if (!GetProjectLoaded())
    {
        qDebug() << "ProjectManager: Could not load the project specified in config.json!";
        return;
    }



    /**
    *Everything went well, emit the signal the project has been successfully loaded
    */
    emit hasLoadedProject();





}



void ProjectManager::UnloadProject()
{




    /**
    *We need the asset loader in order to unload assets
    */
    if (!parent()->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "ProjectManager: Tried to unload project, but could not find the AssetLoader";
        return;
    }



    /**
    *Unload all assets before reloading another project which will have it's
    *own assets
    */
    parent()->findChild<AssetLoader*>("AssetLoader")->UnloadAssets();


    /**
     *Mark that the project has been unloaded
     */
    SetProjectLoaded(false);



    /**
    *If there is no ScriptEngine, create one, it it does, reset it's game
    *object
    */
    if (!parent()->findChild<ScriptEngine*>("ScriptEngine"))
    {



     /**
     *Create the new ScriptEngine
     */
        ScriptEngine * script_engine = new ScriptEngine(parent());


    /**
    *Add required objects to QML context
    */
        script_engine->ConnectToTimer(parent()->findChild<QTimer*>("gTimer"));
        script_engine->RegisterQObject(parent()->findChild<FPS*>("gFPS"));
        script_engine->RegisterQObject(parent()->findChild<InputRegister*>("gInput"));
        script_engine->RegisterQObject(parent()->findChild<AssetLoader*>("AssetLoader"));
        script_engine->RegisterQObject(new aae::Math(script_engine));
    }
    else
        parent()->findChild<ScriptEngine*>("ScriptEngine")->ResetGameObject();




}






void ProjectManager::LoadProjectAndModifyConfig(const QString &project_path)
{



    /**
    *Change the title of the window acording to the path of the project loaded
    */
    parent()->setProperty("windowTitle", QDir(".").relativeFilePath(project_path));



    /**
     *Deserialize config.json
     */
    QJsonObject serialized_config_json = aae::Json::GetJsonFromFile("data/config.json").object();
    QJsonObject serialized_engine_json = serialized_config_json["AaetherEngine"].toObject();


    /**
    *Add the path of the project to the deserialized object
    */
    serialized_engine_json["project"] = QDir(".").relativeFilePath(project_path);
    serialized_config_json["AaetherEngine"] = serialized_engine_json;


    /**
     *Save deserialized object back to config.json
     */
    aae::Json::SaveJsonToFile("data/config.json", QJsonDocument(serialized_config_json));



    /**
     *Proceed to loading the project
     */
    LoadProject();



}



















