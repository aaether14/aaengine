#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H




#include <QThread>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <functional>
#include <QStack>
#include <QDebug>





namespace aae
{



/**
 *@brief The WorkerThread class will provide functionality to run a certain
 *function inside a certain thread
 */
class WorkerThread : public QObject
{


    Q_OBJECT


    /**
     * @brief m_context is a pointer to an opengl context
     */
    QOpenGLContext * m_context;


    /**
     *@brief m_offscreen_surface is an imaginary surface used to make context
     *current for opengl resource loading
     */
    QOffscreenSurface * m_offscreen_surface;


    /**
     *@brief m_functions_stack is a stack of functions that are due to run on
     *this thread
     */
    QStack<std::function<void()> > m_functions_stack;





signals:


    /**
     * @brief check_for_work will signal that thread should check for a job
     */
    void check_for_work();



    /**
     * @brief should_close will singal when the thread should close
     */
    void should_close();



public:



    /**
     * @brief WorkerThread will initialize the worker thread
     * @param context is a pointer to an opengl context
     * @param offscreen_surface is an offscreen surface used to make opengl context current
     */
    WorkerThread(QOpenGLContext * context,
                 QOffscreenSurface * offscreen_surface);





    /**
     * @brief enque_work will enque a function to be run on the thread
     * @param function is the function to be run
     */
    void enque_work(const std::function<void()> & function);




    /**
     * @brief CloseThread will attempt to close the thread
     */
    inline void CloseThread(){
        emit should_close();
    }



};



}



#endif // WORKERTHREAD_H
