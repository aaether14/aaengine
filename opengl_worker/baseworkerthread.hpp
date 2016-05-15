#ifndef BASEWORKERTHREAD_H
#define BASEWORKERTHREAD_H




#include <QThread>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <functional>




namespace aae
{


/**
 *@brief The BaseWorkerThread class is an interface for opengl worker threads
 */
class BaseWorkerThread
{



public:


    /**
     * @brief enque_work should enque a job for the worker thread to accomplish
     * @param function is the job to be done
     */
    virtual void enque_work(const std::function<void()> & function) = 0;


    /**
     * @brief close_thread should close the working thread
     */
    virtual void close_thread() = 0;


    /**
     * @brief ~BaseWorkerThread is a nothing desturctor
     */
    virtual ~BaseWorkerThread();


};


}



#endif // BASEWORKERTHREAD_H
