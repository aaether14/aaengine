#include <core/fps.hpp>





FPS::FPS(QObject *parent) : QObject(parent),
    frame_counter(0),
    fps(0),
    r_delta(0.0),
    total_time(0)
{



    setObjectName("gFPS");
    elapsed_timer = new QTime();




}



FPS::~FPS()
{

    delete elapsed_timer;

}



void FPS::Update()
{



    /**
    *If the timer hasn't yet been turned on, go ahead and start it
    */


    if (!elapsed_timer->isValid())
        elapsed_timer->start();



    /**
    *Increment the frame counter every frame
    */


    frame_counter++;



    /**
    *Compute fps every fixed interval of time
    */


    if (elapsed_timer->elapsed() > FPS_TIME_BETWEEN_COMPUTATIONS)
    {


        /**
        *Compute fps and reset frame counter
        */

        fps = (float)(frame_counter) / (float)(elapsed_timer->elapsed()) * 1000.0;
        frame_counter = 0;


        /**
        *Compute the time elapsed between frames
        */

        r_delta = 1.0 / (float)(fps);


        total_time += elapsed_timer->elapsed();
        elapsed_timer->restart();


        /**
        *Emit a signal that the fps has been recomputed
        */

        emit updatedFps(fps);



    }

}



int FPS::get()
{

    return fps;

}




float FPS::delta()
{

    return r_delta;

}




long long FPS::totalTime()
{


    return total_time;


}



