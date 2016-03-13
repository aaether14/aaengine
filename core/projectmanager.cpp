#include <core/projectmanager.hpp>




ProjectManager::ProjectManager(QObject *parent) : QObject(parent),
    is_project_loaded(false)
{


    setObjectName("ProjectManager");


}




void ProjectManager::LoadProject()
{



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







}



void ProjectManager::UnloadProject()
{




    if (!parent()->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "ProjectManager: Tried to unload project, but could not find the AssetLoader";
        return;
    }




    parent()->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader")->UnloadAssets();
    SetProjectLoaded(false);



    emit resetScriptEngine();




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



















