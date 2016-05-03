#include <core/gl/fps.hpp>






FPS::FPS(QObject *parent) : QObject(parent),
    m_delta_computation_last_recorded_time(0),
    m_last_recorded_time(0),
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





void FPS::Compute()
{





    /**
    *If the timer hasn't yet been turned on, go ahead and start it
    */
    if (!m_elapsed_timer->isValid())
        m_elapsed_timer->start();




    /**
    *Compute delta
    */
    m_delta = (float)(m_elapsed_timer->elapsed() - m_delta_computation_last_recorded_time) / 1000.0;
    m_delta_computation_last_recorded_time = m_elapsed_timer->elapsed();




    /**
    *Increment the frame counter every frame
    */
    m_frame_counter++;



    /**
    *Compute fps every fixed interval of time
    */
    if (m_elapsed_timer->elapsed() - m_last_recorded_time > 1000.0)
    {


        /**
        *Compute fps and reset frame counter
        */
        m_fps = m_frame_counter;
        m_frame_counter = 0;



        /**
        *Add the time between frames and restart the timer
        */
        m_last_recorded_time = m_elapsed_timer->elapsed();


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
    return m_elapsed_timer->elapsed();


}



