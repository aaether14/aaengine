#include <glcontroller.hpp>




GLController::GLController(QWidget *parent)
    : QOpenGLWidget(parent)
{


    QTimer * timer = new QTimer(this);
    timer->setObjectName("gTimer");
    timer->start(0.0);


    FPS * fps = new FPS(this);
    connect(timer, &QTimer::timeout, fps, &FPS::Update);
    connect(timer, &QTimer::timeout, this, &GLController::Update);



    FBXManager * fbx_manager = new FBXManager(this);



}





GLController::~GLController()
{



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
    mesh->LoadFromFBX(findChild<FBXManager*>("FBXManager"), shader, "Bear/bear.fbx");





}



void GLController::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    shader.bind();




    QMatrix4x4 vp = qvariant_cast<QMatrix4x4>(parent()->parent()->findChild<QObject*>("ScriptEngine")->findChild<QObject*>("Default_camera")->property("vp"));


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



