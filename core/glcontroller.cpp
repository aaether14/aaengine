#include <core/glcontroller.hpp>







GLController::GLController(QWidget *parent)
    : QOpenGLWidget(parent),
      is_playing(false)
{




    /**
     *Initialize default timer
     */

    QTimer * timer = new QTimer(this);
    timer->setObjectName("gTimer");
    timer->setInterval(0);



    /**
     *Initialize backup timer that will only be active when the default timer
     *is paused
     */

    QTimer * backup_timer = new QTimer(this);
    backup_timer->setObjectName("gBackupTimer");
    backup_timer->setInterval(0);




    FPS * fps = new FPS(this);
    InputRegister * input = new InputRegister(this);
    AssetLoader * asset_loader = new AssetLoader(this);



    Q_UNUSED(input)
    Q_UNUSED(asset_loader)




    connect(timer, &QTimer::timeout, fps, &FPS::Update);
    connect(timer, &QTimer::timeout, this, &GLController::Update);
    connect(backup_timer, &QTimer::timeout, fps, &FPS::Update);




    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);



}





GLController::~GLController()
{



    makeCurrent();
    doneCurrent();


}






void GLController::initializeGL()
{


    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glClearColor(0.0, 0.0, 0.0, 1.0);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);




    Pipeline * pipeline = new Pipeline(this);
    Q_UNUSED(pipeline)



}



void GLController::paintGL()
{




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




    if (findChild<AssetLoader*>("AssetLoader"))
        findChild<AssetLoader*>("AssetLoader")->LoadStack();




    if (findChild<Pipeline*>("Pipeline"))
        findChild<Pipeline*>("Pipeline")->Render();





}


void GLController::resizeGL(qint32 w, qint32 h)
{

    glViewport(0, 0, w, qMax(h, 1));

}





void GLController::keyPressEvent(QKeyEvent *e)
{


    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterKeyPress(e);


}



void GLController::keyReleaseEvent(QKeyEvent *e)
{

    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterKeyRelease(e);

}




void GLController::mousePressEvent(QMouseEvent *e)
{


    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMousePress(e);


}




void GLController::mouseReleaseEvent(QMouseEvent *e)
{


    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMouseRelease(e);



}




void GLController::mouseMoveEvent(QMouseEvent *e)
{

    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMouseMovement(e);



}





void GLController::Pause()
{


    if (findChild<QTimer*>("gTimer"))
        findChild<QTimer*>("gTimer")->stop();


    if (findChild<QTimer*>("gBackupTimer"))
        findChild<QTimer*>("gBackupTimer")->start();



    is_playing = false;



}




void GLController::Unpause()
{


    if (findChild<QTimer*>("gTimer"))
        findChild<QTimer*>("gTimer")->start();


    if (findChild<QTimer*>("gBackupTimer"))
        findChild<QTimer*>("gBackupTimer")->stop();


    is_playing = true;


}




void GLController::SetPlaying(const bool &playing)
{



    if (playing == true)
        Unpause();
    else
        Pause();



}









void GLController::Update()
{


    update();



}









QString GLController::OpenFileDialog(const QString &file_dialog_name,
                                     const QString &suffix_to_look_for)
{




    bool was_playing = IsPlaying() == true;




    if (was_playing)
        Pause();




    QString project_name = QFileDialog::getOpenFileName(this, file_dialog_name, QString(), suffix_to_look_for);




    if (was_playing)
        Unpause();



    return project_name;




}










