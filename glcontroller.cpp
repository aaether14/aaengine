#include <glcontroller.hpp>




GLController::GLController(QWidget *parent)
    : QOpenGLWidget(parent)
{



    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLController::Update);
    timer->start(0.0);



    FBXManager * fbx_manager = new FBXManager(this);




    elapsed_timer = new QTime();
    elapsed_timer->start();




}





GLController::~GLController()
{


    delete elapsed_timer;


    makeCurrent();
    doneCurrent();


}






void GLController::initializeGL()
{

    initializeOpenGLFunctions();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);




    shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    shader.link();




    findChild<FBXManager*>("FBXManager")->LoadFromFBX("humanoid.fbx", shader);





}



void GLController::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shader.bind();




    mvp.setToIdentity();
    mvp.perspective(60.0f, 1.33f, 0.1f, 100.0f);
    mvp.lookAt(QVector3D(0.0, 0.0, -10.0),
               QVector3D(0.0, 0.0, 0.0),
               QVector3D(0.0, 1.0, 0.0));
    mvp.rotate(elapsed_timer->elapsed() / 4.0, QVector3D(0, 1, 0));
    shader.setUniformValue("MVP", mvp);





    findChild<FBXManager*>("FBXManager")->Draw(this);
    shader.release();





}


void GLController::resizeGL(int w, int h)
{

    glViewport(0, 0, w, qMax(h, 1));

}





void GLController::Update()
{


    update();


}



