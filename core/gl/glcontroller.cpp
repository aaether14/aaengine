#include <core/gl/glcontroller.hpp>







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
     *Create the fps counter the input manager and the asset loader
     */
    FPS * fps = new FPS(this);
    InputRegister * input = new InputRegister(this);
    AssetLoader * asset_loader = new AssetLoader(this);




    /**
    *Mark unused parameters
    */
    Q_UNUSED(input)
    Q_UNUSED(asset_loader)




    /**
     *Connect the rendering to gTimer's update
     */
    connect(timer, &QTimer::timeout, this, &GLController::Update);
    connect(timer, &QTimer::timeout, fps, &FPS::Compute);



    /**
     *Make mouse focus for QOpenGLWidget persistent in relation to other widgets
     */
    setFocusPolicy(Qt::StrongFocus);
    /**
     *Enable mouse tracking
     */
    setMouseTracking(true);







}





GLController::~GLController()
{


#ifdef AAE_USING_OPENGL_DEBUG
    /**
    *Before deleting opengl context we need to stop debug logging
    */
    Logger::Instance()->CloseOpenGLLogging();
#endif


}






void GLController::initializeGL()
{



    /**
     *Set base screen color and enable depth test and face culling
     */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glClearColor(0.0, 0.0, 0.0, 1.0);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);



    /**
     *Initialize the rendering pipeline
     */
    Pipeline * pipeline = new Pipeline(this);
    Q_UNUSED(pipeline)





#ifdef AAE_USING_OPENGL_DEBUG
    if (!QOpenGLContext::currentContext()->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
    {
        qDebug() << "Can't use opengl debug operations!";
    }


    /**
    *Initialize opengl error listening
    */
    Logger::Instance()->InitializeOpenGLLogger();
#endif


    /**
    *Create worker thread share context
    */
    AAEOpenGLWorkerThread::Instance()->CreateContext(context());



}



void GLController::paintGL()
{




    /**
     *First clear the screen to the base color
     */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





    /**
    *If the asset loader exists, append loading operations
    */
    if (findChild<AssetLoader*>("AssetLoader"))
        findChild<AssetLoader*>("AssetLoader")->LoadStack();



    /**
    *If the pipeline exist, append rendering operations
    */
    if (findChild<Pipeline*>("Pipeline"))
        findChild<Pipeline*>("Pipeline")->Render();





}





void GLController::resizeGL(qint32 w, qint32 h)
{

    glViewport(0, 0, qMax(w, 1), qMax(h, 1));

}







QString GLController::OpenFileDialog(const QString &file_dialog_name,
                                     const QString &suffix_to_look_for)
{



    /**
     *Query whether the game was playing or not before dialog opening
     */
    bool was_playing = IsPlaying() == true;



    /**
    *If the game was playing, pause it
    */
    if (was_playing)
        Pause();



    /**
     *Get the name of the file chosen in the dialog
     */
    QString file_name = QFileDialog::getOpenFileName(this, file_dialog_name, QString(), suffix_to_look_for);



    /**
    *If the game was playing, now unpause it
    */
    if (was_playing)
        Unpause();



    /**
    *Return chosen file's name
    */
    return file_name;




}










