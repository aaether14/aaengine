#include <fps.hpp>





FPS::FPS(QObject *parent) : QObject(parent),
    frame_counter(0), fps(0)
{


    setObjectName("gFPS");


    elapsed_timer = new QTime();
    elapsed_timer->start();

}



FPS::~FPS()
{


    delete elapsed_timer;


}



void FPS::Update()
{

    frame_counter++;
    if (elapsed_timer->elapsed() > 1000)
    {
        fps = (float)(frame_counter) / (float)(elapsed_timer->elapsed()) * 1000.0;
        frame_counter = 0;
        elapsed_timer->restart();
    }

}



int FPS::Get()
{
    return fps;
}




float FPS::Delta()
{
    return 1.0/(float)(fps);
}



