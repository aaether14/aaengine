#ifndef AAEOPENGLWORKERTHREAD_H
#define AAEOPENGLWORKERTHREAD_H




#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QSharedPointer>



#include <opengl_worker/workerthread.hpp>




/**
 *@brief The AAEOpenGLWorkerThread class will provide functionality for
 *uploading opengl data in a separate thread
 */
class AAEOpenGLWorkerThread
{



    /**
     *@brief AAEOpenGLWorkerThread is set to private to ensure there will only be a single
     *instance of this singleton
     */
    AAEOpenGLWorkerThread();
    Q_DISABLE_COPY(AAEOpenGLWorkerThread)



    /**
     * @brief m_instance is the instance of the singleton
     */
    static QSharedPointer<AAEOpenGLWorkerThread> m_instance;


    /**
     *@brief m_worker_thread is the thread that will be used to upload opengl
     *data
     */
    static QSharedPointer<aae::WorkerThread> m_worker_thread;


    /**
     * @brief m_context is the opengl context used by the thread
     */
    QOpenGLContext * m_context;



    /**
     *@brief m_offscreen_surface is an offscreen surface used to make context
     *current without actually rendering stuff to it
     */
    QOffscreenSurface * m_offscreen_surface;



public:



    /**
    *@brief ~AAEOpenGLWorkerThread is a basic destructor
    */
    ~AAEOpenGLWorkerThread();



    /**
     * @brief Instance is a basic singleton getter
     * @return singleton instance
     */
    static AAEOpenGLWorkerThread *Instance();



    /**
     * @brief GetThread will get the worker thread
     * @return m_worker_thread;
     */
    inline aae::WorkerThread * GetThread(){
        return m_worker_thread.data();
    }


    /**
     * @brief GetContext will get the context used by the thread
     * @return m_context
     */
    inline QOpenGLContext * GetContext(){
        return m_context;
    }



    /**
     * @brief CreateContext will create the worker thread context and share it to the provided context
     * @param share_context is the context we'll share m_context to
     */
    void CreateContext(QOpenGLContext * share_context);




};

#endif // AAEOPENGLWORKERTHREAD_H
