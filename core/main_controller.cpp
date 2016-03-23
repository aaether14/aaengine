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
    Toggle playing state when prompted
    */
    connect(ui->actionPlay, SIGNAL(toggled(bool)), findChild<GLController*>("GL"), SLOT(SetPlaying(bool)));



    /**
     *Initialize ui dialogs
     */
    Console * console = new Console(this);
    About * about = new About(this);
    MeshImport * mesh_import = new MeshImport(this);


    /**
     * Connect dialogs to corresponding actions
     */
    connect(ui->actionConsole, SIGNAL(triggered(bool)), console, SLOT(onAction()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), about , SLOT(onAction()));
    connect(ui->actionImport, SIGNAL(triggered(bool)), mesh_import, SLOT(onAction()));




    /**
     * Initialize project manager
     */
    ProjectManager * project_manager = new ProjectManager(this);
    /**
    *Whenever loading a project, unpase engine
    */
    connect(project_manager, SIGNAL(hasLoadedProject()), this, SLOT(TogglePlayOnProjectLoad()));
    /**
    *When prompted, reload project
    */
    connect(ui->actionRebuild, SIGNAL(triggered(bool)), project_manager, SLOT(LoadProject()));


    /**
     * Load config.json project
     */
    ResetScriptEngine();
    project_manager->LoadProject();


    /**
    *Every time MainController recieves a signal to reset the script engine, it
    *will do so
    */
    connect(project_manager, SIGNAL(shouldResetScriptEngine()), this, SLOT(ResetScriptEngine()));
    /**
     *Call project_manager->UnloadProject() when close project action is
     *triggered
     */
    connect(ui->actionClose_Project, SIGNAL(triggered(bool)), project_manager, SLOT(UnloadProject()));


    /**
    *Exit when prompted
    */
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));




}





Controller::~Controller()
{

    delete ui;

}





void Controller::ResetScriptEngine()
{



    if (findChild<ScriptEngine*>("ScriptEngine"))
        delete findChild<ScriptEngine*>("ScriptEngine");



    ScriptEngine * script_engine = new ScriptEngine(this);


    /**
    *Add required objects to QML context
    */

    script_engine->ConnectToTimer(findChild<QObject*>("GL")->findChild<QTimer*>("gTimer"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<FPS*>("gFPS"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<InputRegister*>("gInput"));
    script_engine->RegisterQObject(findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader"));
    script_engine->RegisterQObject(new aae::Math(script_engine));



}




void Controller::TogglePlayOnProjectLoad()
{


    /**
    *Check if Play QAction is checked, if not toggle it in order to send a
    *signal to start game loop
    */
    if(!ui->actionPlay->isChecked())
        ui->actionPlay->toggle();


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









