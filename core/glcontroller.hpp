#ifndef GLCONTROLLER_H
#define GLCONTROLLER_H




#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_3_Core>



#include <QMatrix4x4>
#include <QTimer>
#include <QDebug>
#include <QMetaProperty>



#include <fbx_manager/fbxmanager.hpp>
#include <core/fps.hpp>
#include <core/inputregister.hpp>
#include <renderer/pipeline.hpp>
#include <assets/assetloader.hpp>




/**
 *@brief The GLController class controls opengl activity of the engine
 */
class GLController : public QOpenGLWidget
{


    Q_OBJECT




public:


    /**
     * @brief GLController will intialize update timer and fps computer
     * @param parent
     */
    explicit GLController(QWidget * parent = 0);
    /**
    @brief ~GLController - basic destructor
    */
    ~GLController();


    /**
     * @brief initializeGL will intialize GL context
     */
    void initializeGL();
    /**
     * @brief paintGL will handle the GL rendering
     */
    void paintGL();
    /**
     * @brief resizeGL will handle viewport resize
     * @param w - width of viewport
     * @param h - height of viewport
     */
    void resizeGL(int w, int h);



    /**
     * @brief keyPressEvent watches for key press events and registers them
     * @param e is the event
     */
    void keyPressEvent(QKeyEvent * e);
    /**
     * @brief keyReleaseEvent watches for key release events and registers them
     * @param e is the event
     */
    void keyReleaseEvent(QKeyEvent * e);
    /**
     * @brief mousePressEvent watches for mouse press events and registers them
     * @param e is the event
     */
    void mousePressEvent(QMouseEvent * e);
    /**
     * @brief mouseReleaseEvent watches for mouse release events and registers them
     * @param e is the event
     */
    void mouseReleaseEvent(QMouseEvent * e);
    /**
     * @brief mouseMoveEvent watches for mouse move events and registers them
     * @param e is the event
     */
    void mouseMoveEvent(QMouseEvent * e);



    /**
     * @brief Pause will pause the QTimer
     */
    void Pause();


    /**
     *@brief will unpase the QTimer
    */
    void Unpause();





signals:



private slots:

    /**
     * @brief Update will set the internal QOpenGLWidget update() method
     */
    void Update();



};

#endif // GLCONTROLLER_H
