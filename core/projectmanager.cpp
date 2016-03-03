#include <core/projectmanager.hpp>




ProjectManager::ProjectManager(QObject *parent) : QObject(parent),
    is_project_loaded(false)
{




    setObjectName("ProjectManager");



    config_json = Json::GetJsonFromFile("data/config.json");
    LoadProject(config_json.toVariant().toMap()["AaetherEngine"].toMap()["project"].toString());



    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+R"), qobject_cast<QWidget*>(parent));
    connect(shortcut, &QShortcut::activated, [=]() {

        LoadProject(config_json.toVariant().toMap()["AaetherEngine"].toMap()["project"].toString());
    });




}




void ProjectManager::LoadProject(QString project_name)
{



    UnloadProject();




    if (parent()->findChild<ScriptEngine*>("ScriptEngine"))
    {



        ScriptEngine * se = parent()->findChild<ScriptEngine*>("ScriptEngine");
        SetProjectLoaded(se->LoadProject("data/settings/settings.qml"));



        if (!GetProjectLoaded())
            qDebug() << "ProjectManager: Could not load the project " << project_name << "!";



    }
    else
        qDebug() << "ProjectManager: Could not find the ScriptEngine!";





}



void ProjectManager::UnloadProject()
{




    if (!parent()->findChild<QObject*>("ScriptEngine"))
    {
        qDebug() << "ProjectManager: Tried to unload project, but could not find the ScriptEngine!";
        return;
    }




    if (parent()->findChild<QObject*>("ScriptEngine")->findChild<QObject*>("Settings"))
        delete parent()->findChild<QObject*>("ScriptEngine")->findChild<QObject*>("Settings");





    if (!parent()->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "ProjectManager: Tried to unload project, but could not find the AssetLoader";
        return;
    }




    parent()->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader")->UnloadAssets();
    SetProjectLoaded(false);




}
