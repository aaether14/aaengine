#include <core/main_controller.hpp>
#include "ui_controller.h"







Controller::Controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controller)
{


    /**
      Basic ui setup
    */
    ui->setupUi(this);



    /**
     *Initialize ui dialogs
     */
    Console * console = new Console(this);
    About * about = new About(this);
    MeshImport * mesh_import = new MeshImport(this);




    /**
     * Initialize project manager
     */
    ProjectManager * project_manager = new ProjectManager(this);


    /**
     * Load config.json project
     */
    ResetScriptEngine();
    project_manager->LoadProject();
    connect(project_manager, SIGNAL(resetScriptEngine()), this, SLOT(ResetScriptEngine()));




    /**
    *Check if Play QAction is checked, if not toggle it in order to send a
    *signal to start game loop
    */
    if(!ui->actionPlay->isChecked())
        ui->actionPlay->toggle();




    Q_UNUSED(console)
    Q_UNUSED(about)
    Q_UNUSED(mesh_import)




}





Controller::~Controller()
{
    delete ui;
}




void Controller::on_actionConsole_triggered()
{


    if (findChild<baseDialog*>("Console"))
        findChild<baseDialog*>("Console")->onAction();



}




void Controller::on_actionAbout_triggered()
{

    if (findChild<baseDialog*>("About"))
        findChild<baseDialog*>("About")->onAction();


}






void Controller::on_actionProject_triggered()
{



    if (!findChild<GLController*>("GL"))
    {
        qDebug() << "MainController: No GL controller detected!";
        return;
    }






    QString project_name = findChild<GLController*>("GL")->OpenFileDialog("Open Project", "*.qml");





    if (!project_name.size())
        return;




    if (!findChild<ProjectManager*>("ProjectManager"))
    {
        qDebug() << "MainController: Could not load: " << project_name << " because ProjectManager was not found!";
        return;
    }




    findChild<ProjectManager*>("ProjectManager")->LoadProjectAndModifyConfig(project_name);






}




void Controller::on_actionExit_triggered()
{


    close();


}




void Controller::on_actionRebuild_triggered()
{



    if (!findChild<ProjectManager*>("ProjectManager"))
    {
        qDebug() << "MainController: Could not find ProjectManager in order to reload project!";
        return;
    }



    if (!ui->actionPlay->isChecked())
        ui->actionPlay->toggle();



    findChild<ProjectManager*>("ProjectManager")->LoadProject();



}




void Controller::on_actionPlay_toggled(bool arg1)
{



    if (!findChild<GLController*>("GL"))
    {
        qDebug() << "MainController: No GL controller detected! (play toggle)";
        return;
    }



    findChild<GLController*>("GL")->SetPlaying(arg1);




}







void Controller::on_actionImport_triggered()
{



    if (findChild<baseDialog*>("MeshImport"))
        findChild<baseDialog*>("MeshImport")->onAction();




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
    script_engine->RegisterQObject(new aae::Math(script_engine));



}


