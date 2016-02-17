#ifndef GLCONTROLLER_H
#define GLCONTROLLER_H




#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_3_Core>



#include <QMatrix4x4>
#include <QTimer>
#include <QDebug>




#include <core/fps.hpp>
#include <core/inputregister.hpp>
#include <renderer/pipeline.hpp>




class GLController : public QOpenGLWidget
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



    void keyPressEvent(QKeyEvent * e);
    void keyReleaseEvent(QKeyEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);



signals:



private slots:
    void Update();



};

#endif // GLCONTROLLER_H
