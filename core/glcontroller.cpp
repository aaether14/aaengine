#include <core/glcontroller.hpp>




GLController::GLController(QWidget *parent)
    : QOpenGLWidget(parent)
{




    QTimer * timer = new QTimer(this);
    timer->setObjectName("gTimer");
    timer->start(0.0);




    FPS * fps = new FPS(this);
    InputRegister * input = new InputRegister(this);
    AssetLoader * asset_loader = new AssetLoader(this);




    connect(timer, &QTimer::timeout, fps, &FPS::Update);
    connect(timer, &QTimer::timeout, this, &GLController::Update);




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
    f->glClearColor(0.8, 0.85, 0.9, 1.0);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);




    Pipeline * pipeline = new Pipeline(this);



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


void GLController::resizeGL(int w, int h)
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





void GLController::Update()
{


    update();



}



