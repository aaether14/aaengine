#include <core/projectmanager.hpp>




ProjectManager::ProjectManager(QObject *parent) : QObject(parent),
    is_project_loaded(false)
{


    setObjectName("ProjectManager");


}




void ProjectManager::LoadProject()
{




    if (!parent()->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "ProjectManager: Had to check if all assets are loaded, but could not find the AssetLoader";
        return;
    }


    if(!parent()->findChild<AssetLoader*>("AssetLoader")->SanityCheck())
    {

        qDebug() << "ProjectManager: Assets are not all loaded successfully, so it's dangerous to reload, aborted!";
        return;

    }



    config_json = aae::Json::GetJsonFromFile("data/config.json");
    UnloadProject();



    if (!parent()->findChild<ScriptEngine*>("ScriptEngine"))
    {
        qDebug() << "ProjectManager: Could not find the ScriptEngine!";
        return;
    }



    ScriptEngine * se = parent()->findChild<ScriptEngine*>("ScriptEngine");
    SetProjectLoaded(se->LoadProject(config_json.toVariant().toMap()["AaetherEngine"].toMap()["project"].toString()));



    if (!GetProjectLoaded())
        qDebug() << "ProjectManager: Could not load the project specified in config.json!";





    emit hasLoadedProject();





}



void ProjectManager::UnloadProject()
{




    if (!parent()->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "ProjectManager: Tried to unload project, but could not find the AssetLoader";
        return;
    }




    parent()->findChild<AssetLoader*>("AssetLoader")->UnloadAssets();
    SetProjectLoaded(false);



    emit shouldResetScriptEngine();




}






void ProjectManager::LoadProjectAndModifyConfig(QString project_path)
{



    parent()->setProperty("windowTitle", QDir(".").relativeFilePath(project_path));




    QJsonObject serialized_config_json = aae::Json::GetJsonFromFile("data/config.json").object();
    QJsonObject serialized_engine_json = serialized_config_json["AaetherEngine"].toObject();



    serialized_engine_json["project"] = QDir(".").relativeFilePath(project_path);
    serialized_config_json["AaetherEngine"] = serialized_engine_json;



    aae::Json::SaveJsonToFile("data/config.json", QJsonDocument(serialized_config_json));



    LoadProject();



}



















