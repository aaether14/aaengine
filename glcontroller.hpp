#ifndef GLCONTROLLER_H
#define GLCONTROLLER_H




#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <fbx_manager/fbxmanager.hpp>




class GLController : public QOpenGLWidget, public QOpenGLFunctions
{


    Q_OBJECT
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLShaderProgram shader;
    QMatrix4x4 mvp;


    QTime * elapsed_timer;



public:


    explicit GLController(QWidget * parent = 0);
    ~GLController();


    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);



signals:

private slots:
    void Update();



};

#endif // GLCONTROLLER_H
