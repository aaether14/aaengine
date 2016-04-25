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



    /**
    *If there is any ScriptEngine in the hierarchy tree delete it before
    *creating a new one
    */
    if (findChild<ScriptEngine*>("ScriptEngine"))
        delete findChild<ScriptEngine*>("ScriptEngine");



    /**
     *Create the new ScriptEngine
     */
    ScriptEngine * script_engine = new ScriptEngine(this);


    /**
    *Add required objects to QML context
    */
    script_engine->ConnectToTimer(findChild<QTimer*>("gTimer"));
    script_engine->RegisterQObject(findChild<FPS*>("gFPS"));
    script_engine->RegisterQObject(findChild<InputRegister*>("gInput"));
    script_engine->RegisterQObject(findChild<AssetLoader*>("AssetLoader"));
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




    /**
    *We first the GLController that will need to pause in order to open the
    *file dialog and then pop it
    */
    if (!findChild<GLController*>("GL"))
    {
        qDebug() << "MainController: No GL controller detected!";
        return;
    }



    /**
     *Open the file diloag and let the user chose the project he wants to open
     */
    QString project_name = findChild<GLController*>("GL")->OpenFileDialog("Open Project", "*.qml");



    /**
    *No project has chosen. Abort!
    */
    if (!project_name.size())
        return;




    /**
    *We need the project manager in order to do the loading. If for some reason it's not there abort.
    */
    if (!findChild<ProjectManager*>("ProjectManager"))
    {
        qDebug() << "MainController: Could not load: " << project_name << " because ProjectManager was not found!";
        return;
    }



    /**
    *Load the chosen project and also modify config.json to by default load
    *this project
    */
    findChild<ProjectManager*>("ProjectManager")->LoadProjectAndModifyConfig(project_name);






}




void Controller::closeEvent(QCloseEvent *event)
{



    /**
    *If there is no asset loader there might be no assets loading so go ahead
    *and proceed to quiting the application
    */
    if (!findChild<AssetLoader*>("AssetLoader"))
    {
        event->accept();
        return;
    }


    if (!findChild<AssetLoader*>("AssetLoader")->SanityCheck())
    {
        qDebug() << "MainController: Not all assets have finished loading so it's unsafe to quit. Aborted!";
        event->ignore();
        return;
    }



    /**
    *If everything went well go ahead and close the window
    */
    event->accept();



}









