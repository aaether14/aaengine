#include <glcontroller.hpp>





GLController::GLController(QWidget *parent)
    : QGLWidget(parent)
{



    QGLFormat format;
    format.setVersion(4, 3);
    setFormat(format);



    move(50, 50);
    resize(800, 600);
    setObjectName("GLController");



    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLController::Update);
    timer->start(0);



}




void GLController::initializeGL()
{

    glClearColor(0.0, 0.0, 0.0, 1.0);

}



void GLController::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT);


}


void GLController::resizeGL(int w, int h)
{


}





void GLController::Update()
{



}



