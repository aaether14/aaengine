#include <core/main_controller.hpp>
#include "ui_controller.h"





Controller::Controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controller)
{



    ui->setupUi(this);




    ProjectManager * project_manager = new ProjectManager(this);



    ResetScriptEngine();
    project_manager->LoadProject();
    connect(project_manager, SIGNAL(resetScriptEngine()), this, SLOT(ResetScriptEngine()));




    Console * console = new Console(this);
    About * about = new About(this);




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
        findChild<Console*>("Console")->show();



}




void Controller::on_actionAbout_triggered()
{

    if (findChild<About*>("About"))
        findChild<About*>("About")->show();

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





