#ifndef GLCONTROLLER_H
#define GLCONTROLLER_H




#include <QGLWidget>
#include <QGLFormat>
#include <QTimer>
#include <QDebug>




class GLController : public QGLWidget
{
    Q_OBJECT



public:


    explicit GLController(QWidget * parent = 0);


    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);



signals:

private slots:
    void Update();
};

#endif // GLCONTROLLER_H
