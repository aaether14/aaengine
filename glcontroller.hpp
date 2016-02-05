#ifndef GLCONTROLLER_H
#define GLCONTROLLER_H




#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QTimer>
#include <QDebug>
#include <fbx_manager/mesh.hpp>
#include <fps.hpp>




class GLController : public QOpenGLWidget, public QOpenGLFunctions
{


    Q_OBJECT



    QOpenGLShaderProgram shader;
    Mesh * mesh;




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
