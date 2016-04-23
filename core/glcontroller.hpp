#ifndef GLCONTROLLER_H
#define GLCONTROLLER_H




#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_3_Core>



#include <QTimer>
#include <QDebug>
#include <QFileDialog>



#include <fbx_manager/fbxmanager.hpp>
#include <core/fps.hpp>
#include <core/inputregister.hpp>
#include <renderer/pipeline.hpp>
#include <assets/assetloader.hpp>
#include <opengl_worker/aaeopenglworkerthread.hpp>
#include <dialogs/console/logger.hpp>



/**
 *@brief The GLController class controls opengl activity of the engine
 */
class GLController : public QOpenGLWidget
{


    Q_OBJECT



    /**
     *@brief is_playing will be true if the game is unpaused and false
     *otherwise
     */
    bool is_playing;




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
    void resizeGL(qint32 w, qint32 h);



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



    /**
     * @brief IsPlaying will return whether the game is paused or not
     * @return is_playing private member;
     */
    inline const bool &IsPlaying() const{
        return is_playing;
    }




    /**
     * @brief OpenFileDialog will open a file dialog and return the file you chose,
     * it will also pause the engine while the file dialog is opened and unpause after
     * that
     * @param file_dialog_name is the name of the file dialog
     * @param suffix_to_look_for is the suffix of the files the file dialog will look for
     * @return the name of the file you chose from the dialog
     */
    QString OpenFileDialog(const QString &file_dialog_name,
                           const QString &suffix_to_look_for);





signals:


public slots:


    /**
     * @brief SetPlaying will set whether the game is playing or not
     * @param playing is the value that is_playing will be set to
     */
    void SetPlaying(const bool &playing);


private slots:

    /**
     * @brief Update will set the internal QOpenGLWidget update() method
     */
    inline void Update(){
        update();
    }



};

#endif // GLCONTROLLER_H
