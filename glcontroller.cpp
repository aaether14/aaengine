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
    delete mesh;
    doneCurrent();


}






void GLController::initializeGL()
{


    initializeOpenGLFunctions();
    glClearColor(0.8, 0.85, 0.9, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);




    shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    shader.link();




    mesh = new Mesh();
    mesh->LoadFromFBX(findChild<FBXManager*>("FBXManager"), shader, "Street/street.fbx");





}



void GLController::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    shader.bind();


    QMatrix4x4 vp;
    vp.setToIdentity();
    vp.perspective(60.0f, 1.33f, 0.1f, 300.0f);
    vp.lookAt(QVector3D(0.0, 0.0, -100.0),
               QVector3D(0.0, 0.0, 0.0),
               QVector3D(0.0, 1.0, 0.0));


    QMatrix4x4 m;
    m.scale(3.0);
    m.rotate(-120, QVector3D(1, 0, 0));


    shader.setUniformValue("MVP", vp * m);
    shader.setUniformValue("M", m);





    mesh->Draw(this);
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



