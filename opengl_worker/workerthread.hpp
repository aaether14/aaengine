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
class WorkerThread : public QThread
{


    /**
     * @brief m_function is the function to be run by this thread
     */
    std::function<void()> m_function;


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



    /**
     * @brief will call the internal function pointer
     */
    void run();




private slots:
    /**
     * @brief work will run the next function in the stack
     */
    void work();



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



};



}



#endif // WORKERTHREAD_H
