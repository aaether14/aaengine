#include <glcontroller.hpp>




GLController::GLController(QWidget *parent)
    : QOpenGLWidget(parent),
      ibo(QOpenGLBuffer::IndexBuffer)
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



    findChild<FBXManager*>("FBXManager")->LoadFromFBX("humanoid.fbx");





    vao.create();
    vao.bind();


    shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    shader.link();




    float vertices[] = {

        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,

        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
    };



    unsigned int indices[] = {

        0, 1, 2,
        2, 3, 0,

        1, 5, 6,
        6, 2, 1,


        7, 6, 5,
        5, 4, 7,

        4, 0, 3,
        3, 7, 4,

        4, 5, 1,
        1, 0, 4,


        3, 2, 6,
        6, 7, 3,
    };





    shader.bind();
    vbo.create();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.bind();
    vbo.allocate(vertices, 8 * 3 * sizeof(float));


    shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
    shader.enableAttributeArray("vertex");



    ibo.create();
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.bind();
    ibo.allocate(indices, 12 * 3 * sizeof(unsigned int));




    vbo.release();
    shader.release();
    vao.release();







}



void GLController::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    vao.bind();
    shader.bind();



    mvp.setToIdentity();
    mvp.perspective(60.0f, 1.33f, 0.1f, 100.0f);
    mvp.lookAt(QVector3D(0.0, 0.0, -5.0),
               QVector3D(0.0, 0.0, 0.0),
               QVector3D(0.0, 1.0, 0.0));
    mvp.rotate(elapsed_timer->elapsed() / 4.0, QVector3D(0, 1, 0));
    shader.setUniformValue("MVP", mvp);



    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    shader.release();
    vao.release();





}


void GLController::resizeGL(int w, int h)
{

    glViewport(0, 0, w, qMax(h, 1));

}





void GLController::Update()
{


    update();


}



