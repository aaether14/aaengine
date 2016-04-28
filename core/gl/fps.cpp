#include <core/gl/fps.hpp>




quint64 FPS::m_total_time = 0;




FPS::FPS(QObject *parent) : QObject(parent),
    m_frame_counter(0),
    m_fps(0),
    m_delta(0.0)
{


    /**
     *Set the name of the QObject
     */
    setObjectName("gFPS");
    /**
    *Allocate memory for the timer that will measure time between frames
    */
    m_elapsed_timer = new QTime();




}



FPS::~FPS()
{

    /**
    *Delete the timer
    */
    delete m_elapsed_timer;

}



void FPS::Update()
{



    /**
    *If the timer hasn't yet been turned on, go ahead and start it
    */
    if (!m_elapsed_timer->isValid())
        m_elapsed_timer->start();



    /**
    *Increment the frame counter every frame
    */
    m_frame_counter++;



    /**
    *Compute fps every fixed interval of time
    */
    if (m_elapsed_timer->elapsed() > FPS_TIME_BETWEEN_COMPUTATIONS)
    {


        /**
        *Compute fps and reset frame counter
        */

        m_fps = (float)(m_frame_counter) / (float)(m_elapsed_timer->elapsed()) * 1000.0;
        m_frame_counter = 0;


        /**
        *Compute the time elapsed between frames
        */
        m_delta = 1.0 / (float)(m_fps);


        /**
        *Add the time between frames and restart the timer
        */
        m_total_time += m_elapsed_timer->elapsed();
        m_elapsed_timer->restart();


        /**
        *Emit a signal that the fps has been recomputed
        */
        emit updatedFps(m_fps);



    }

}



qint32 FPS::get()
{

    /**
    *Get the framerate of the game
    */
    return m_fps;

}




float FPS::delta()
{

    /**
    *Get the time between frames
    */
    return m_delta;

}




quint64 FPS::totalTime()
{

    /**
    *Get total elapsed time from the start of the game (msecs)
    */
    return m_total_time;


}



