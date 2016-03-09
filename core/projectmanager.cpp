#include <core/projectmanager.hpp>




ProjectManager::ProjectManager(QObject *parent) : QObject(parent),
    is_project_loaded(false)
{




    setObjectName("ProjectManager");



    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+R"), qobject_cast<QWidget*>(parent));
    connect(shortcut, &QShortcut::activated, [=]() {
        LoadProject();
    });




}




void ProjectManager::LoadProject()
{



    config_json = Json::GetJsonFromFile("data/config.json");



    UnloadProject();
    emit resetScriptEngine();





    if (parent()->findChild<ScriptEngine*>("ScriptEngine"))
    {




        ScriptEngine * se = parent()->findChild<ScriptEngine*>("ScriptEngine");
        se->RegisterQObject(this);



        SetProjectLoaded(se->LoadProject(config_json.toVariant().toMap()["AaetherEngine"].toMap()["project"].toString()));



        if (!GetProjectLoaded())
            qDebug() << "ProjectManager: Could not load the project specified in config.json!";



    }
    else
        qDebug() << "ProjectManager: Could not find the ScriptEngine!";





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




}
