#include <opengl_worker/workerthread2.hpp>




namespace aae
{




WorkerThread2::WorkerThread2(QOpenGLContext *context,
                             QOffscreenSurface *offscreen_surface)
{


    /**
    *Set the pointers to opengl context and offscreen surface used to make
    *context current
    */
    m_context = context;
    m_offscreen_surface = offscreen_surface;


    /**
    *Move opengl context to worker thread
    */
    m_context->moveToThread(this);



    /**
    *Each time the thread finishes a job it chould check if another one is
    *available
    */
    connect(this, &QThread::finished, this, [=]{
        if (!m_functions_stack.isEmpty())
            start();
    });



}




void WorkerThread2::run()
{


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


}




void WorkerThread2::enque_work(const std::function<void ()> &function)
{


    /**
    *First enque the function in the stack
    */
    m_functions_stack.push(function);


    /**
    *If the thread is idle, append a job
    */
    if (!isRunning())
        start();



}




}








