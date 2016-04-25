#include <opengl_worker/workerthread.hpp>





namespace aae
{






void WorkerThread::run()
{



    m_context->makeCurrent(m_offscreen_surface);
    m_function();
    m_context->doneCurrent();



}




void WorkerThread::work()
{



    /**
    *If there are available jobs append one
    */
    if (!m_functions_stack.isEmpty())
    {
        m_function = m_functions_stack.pop();
        start();
    }



}





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
     *Make it so each time a thread finished a job it checks if there's another
     *one available
     */
    connect(this, &QThread::finished, this, &WorkerThread::work);



}






void WorkerThread::enque_work(const std::function<void ()> &function)
{


    /**
    *First enque the function in the stack
    */
    m_functions_stack.push(function);


    /**
    *Thread is already doing something
    */
    if (isRunning())
        return;


    /**
     *If the thread does nothing ATM give it a job
     */
    work();



}





}
