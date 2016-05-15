#ifndef WORKERTHREAD2_H
#define WORKERTHREAD2_H



#include <QStack>
#include <QDebug>



#include <opengl_worker/baseworkerthread.hpp>




namespace aae
{



/**
 *@brief The WorkerThread2 class will provide an alternative for WorkerThread.
 *It may work slower in some cases but it should fix the stalls when using
 *cached draw
 */
class WorkerThread2 : public QThread, public aae::BaseWorkerThread
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



public:


    /**
     * @brief WorkerThread will initialize the worker thread
     * @param context is a pointer to an opengl context
     * @param offscreen_surface is an offscreen surface used to make opengl context current
     */
    WorkerThread2(QOpenGLContext * context,
                 QOffscreenSurface * offscreen_surface);



    /**
     *This will be the behaviour of the thread
     */
    void run();



    /**
     * @brief enque_work will enque a function to be run on the thread
     * @param function is the function to be run
     */
    void enque_work(const std::function<void()> & function);



    /**
     * @brief close_thread will do nothing in this case
     */
    void close_thread(){}



};




}


#endif // WORKERTHREAD2_H








