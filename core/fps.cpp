#include <core/fps.hpp>





FPS::FPS(QObject *parent) : QObject(parent),
    frame_counter(0), fps(0), r_delta(0.0)
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


    if (!elapsed_timer->isValid())
        elapsed_timer->start();



    frame_counter++;
    if (elapsed_timer->elapsed() > 100)
    {


        fps = (float)(frame_counter) / (float)(elapsed_timer->elapsed()) * 1000.0;
        frame_counter = 0;


        r_delta = 1.0 / (float)(fps);
        elapsed_timer->restart();


        emit updatedFps(fps);



    }

}



int FPS::Get()
{
    return fps;
}




float FPS::Delta()
{
    return r_delta;
}



