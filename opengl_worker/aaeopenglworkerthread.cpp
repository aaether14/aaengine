#include <opengl_worker/aaeopenglworkerthread.hpp>





QSharedPointer<AAEOpenGLWorkerThread> AAEOpenGLWorkerThread::m_instance;
QSharedPointer<aae::WorkerThread> AAEOpenGLWorkerThread::m_worker_thread;





AAEOpenGLWorkerThread::AAEOpenGLWorkerThread()
{




}



AAEOpenGLWorkerThread::~AAEOpenGLWorkerThread()
{


    delete m_offscreen_surface;


}





AAEOpenGLWorkerThread *AAEOpenGLWorkerThread::Instance()
{


    if (m_instance.isNull())
        m_instance.reset(new AAEOpenGLWorkerThread);


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


    m_context->moveToThread(m_worker_thread.data());




}

















