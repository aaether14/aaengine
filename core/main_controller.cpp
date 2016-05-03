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
    project_manager->LoadProject();



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

    /**
    *Just delete the ui
    */
    delete ui;

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




    AAEOpenGLWorkerThread::Instance()->GetThread()->CloseThread();




}









