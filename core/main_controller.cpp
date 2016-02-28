#include <core/main_controller.hpp>
#include "ui_controller.h"





Controller::Controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controller)
{



    ui->setupUi(this);



    ScriptEngine * script_engine = new ScriptEngine(this);
    script_engine->ConnectToTimer(findChild<QObject*>("GL")->findChild<QTimer*>("gTimer"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<FPS*>("gFPS"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<InputRegister*>("gInput"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader"));
    script_engine->RegisterQObject(new Math(this));





    if (QFileInfo("data/settings/settings.qml").exists())
        script_engine->AddQMLScript("data/settings/settings.qml", false);
    else
        qDebug() << "Could not load settings!";






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





