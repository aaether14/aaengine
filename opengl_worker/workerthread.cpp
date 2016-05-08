#include <opengl_worker/workerthread.hpp>




namespace aae
{









WorkerThread::WorkerThread(QOpenGLContext *context,
                           QOffscreenSurface *offscreen_surface)
{


    /**
    *Set the pointers to opengl context and offscreen surface used to make
    *context current
    */
    m_context = context;
    m_offscreen_surface = offscreen_surface;



    /**
     *Create the thread
     */
    QThread * thread = new QThread();


    /**
    *Use provided context on this thread
    */
    m_context->moveToThread(thread);




    /**
     *Move the worker to thread
     */
    moveToThread(thread);





    /**
     *Every time a job is available, try to do it
     */
    connect(this, &WorkerThread::check_for_work, this, [=](){


        /**
        *Make the context current against offscreen surface
        */
        m_context->makeCurrent(m_offscreen_surface);


        /**
        *If there is any job try it
        */
        if (!m_functions_stack.isEmpty())
            m_functions_stack.pop()();


        /**
        *Release context
        */
        m_context->doneCurrent();


    });
    /**
    *If the thread was requested to close do so
    */
    connect(this, &WorkerThread::should_close, this, [=](){
        thread->quit();
        thread->deleteLater();
    });





    /**
    *Start the thread
    */
    thread->start();




}








void WorkerThread::enque_work(const std::function<void ()> &function)
{


    /**
    *First enque the function in the stack
    */
    m_functions_stack.push(function);



    /**
    *Issue a new job
    */
    emit check_for_work();




}





}
