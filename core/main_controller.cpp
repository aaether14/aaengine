#include <core/main_controller.hpp>
#include "ui_controller.h"





Controller::Controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controller)
{



    ui->setupUi(this);



    Console * console = new Console(this);
    About * about = new About(this);



    ProjectManager * project_manager = new ProjectManager(this);



    ResetScriptEngine();
    project_manager->LoadProject();
    connect(project_manager, SIGNAL(resetScriptEngine()), this, SLOT(ResetScriptEngine()));





    Q_UNUSED(console)
    Q_UNUSED(about)




}





Controller::~Controller()
{
    delete ui;
}




void Controller::on_actionConsole_triggered()
{


    if (findChild<Console*>("Console"))
        findChild<Console*>("Console")->onAction();



}




void Controller::on_actionAbout_triggered()
{

    if (findChild<About*>("About"))
        findChild<About*>("About")->onAction();


}








void Controller::on_actionProject_triggered()
{


    if (findChild<GLController*>("GL"))
        findChild<GLController*>("GL")->Pause();
    else
    {
        qDebug() << "MainController: No GL controller detected!";
        return;
    }



    QString project_name = QFileDialog::getOpenFileName(this, "Open Project", QString(), "*.qml");



    findChild<GLController*>("GL")->Unpause();





    if (!project_name.size())
        return;



    setProperty("windowTitle", QDir(".").relativeFilePath(project_name));



    if (!findChild<ProjectManager*>("ProjectManager"))
    {
        qDebug() << "MainController: Could not load: " << project_name << " because ProjectManager was not found!";
        return;
    }




    QJsonObject serialized_config_json = Json::GetJsonFromFile("data/config.json").object();
    QJsonObject serialized_engine_json = serialized_config_json["AaetherEngine"].toObject();



    serialized_engine_json["project"] = QDir(".").relativeFilePath(project_name);
    serialized_config_json["AaetherEngine"] = serialized_engine_json;



    Json::SaveJsonToFile("data/config.json", QJsonDocument(serialized_config_json));



    findChild<ProjectManager*>("ProjectManager")->LoadProject();



}




void Controller::on_actionExit_triggered()
{



    close();



}





void Controller::ResetScriptEngine()
{



    if (findChild<ScriptEngine*>("ScriptEngine"))
        delete findChild<ScriptEngine*>("ScriptEngine");



    ScriptEngine * script_engine = new ScriptEngine(this);


    script_engine->ConnectToTimer(findChild<QObject*>("GL")->findChild<QTimer*>("gTimer"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<FPS*>("gFPS"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<InputRegister*>("gInput"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader"));
    script_engine->RegisterQObject(new Math(script_engine));



}

