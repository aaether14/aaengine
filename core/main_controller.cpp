#include <core/main_controller.hpp>
#include "ui_controller.h"





QString Controller::OpenFileDialog(QString file_dialog_name, QString suffix_to_look_for)
{



    if (!findChild<GLController*>("GL"))
    {
        qDebug() << "MainController: No GL controller detected! (project loading)";
        return QString();
    }





    bool was_playing = findChild<GLController*>("GL")->IsPlaying() == true;




    if (was_playing)
        findChild<GLController*>("GL")->Pause();




    QString project_name = QFileDialog::getOpenFileName(this, file_dialog_name, QString(), suffix_to_look_for);




    if (was_playing)
        findChild<GLController*>("GL")->Unpause();



    return project_name;




}







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




    QString project_name = OpenFileDialog("Open Project", "*.qml");



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



    if (findChild<MeshImport*>("MeshImport"))
        findChild<MeshImport*>("MeshImport")->onAction();




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


