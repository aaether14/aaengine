#include <opengl_worker/aaeopenglworkerthread.hpp>





QSharedPointer<AAEOpenGLWorkerThread> AAEOpenGLWorkerThread::m_instance;
QSharedPointer<aae::WorkerThread> AAEOpenGLWorkerThread::m_worker_thread;







AAEOpenGLWorkerThread::~AAEOpenGLWorkerThread()
{


    /**
    *Release resources used by offscreen surface
    */
    if (m_offscreen_surface)
        m_offscreen_surface->destroy();



}





AAEOpenGLWorkerThread *AAEOpenGLWorkerThread::Instance()
{


    /**
    *If the singleton instance has not yet been created, go ahead and do it
    */
    if (m_instance.isNull())
        m_instance.reset(new AAEOpenGLWorkerThread);


    /**
    *Return a pointer to the instance
    */
    return m_instance.data();


}





void AAEOpenGLWorkerThread::CreateContext(QOpenGLContext *share_context)
{



    /**
    *First create context
    */
    m_context = new QOpenGLContext();
    m_context->setFormat(share_context->format());
    m_context->setShareContext(share_context);
    m_context->create();



    /**
    Create offscreen surface
    */
    m_offscreen_surface = new QOffscreenSurface();
    m_offscreen_surface->setFormat(m_context->format());
    m_offscreen_surface->create();



    /**
    *Create the worker thread
    */
    m_worker_thread.reset(new aae::WorkerThread(m_context,
                                                m_offscreen_surface));


    /**
    *Move the context to the worker thread
    */
    m_context->moveToThread(m_worker_thread.data());




}

















