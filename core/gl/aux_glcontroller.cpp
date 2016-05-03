#include <core/gl/glcontroller.hpp>






void GLController::keyPressEvent(QKeyEvent *e)
{


    /**
    *Register a key press event
    */
    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterKeyPress(e);


}





void GLController::keyReleaseEvent(QKeyEvent *e)
{

    /**
    *Register a key release event
    */
    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterKeyRelease(e);

}





void GLController::mousePressEvent(QMouseEvent *e)
{


    /**
    *Register a mouse press event
    */
    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMousePress(e);


}




void GLController::mouseReleaseEvent(QMouseEvent *e)
{


    /**
    *Register a mouse release event
    */
    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMouseRelease(e);



}




void GLController::mouseMoveEvent(QMouseEvent *e)
{

    /**
    *Register a mouse move event
    */
    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMouseMovement(e);



}






void GLController::Pause()
{


    /**
    *Pause the main timer
    */
    if (findChild<QTimer*>("gTimer"))
        findChild<QTimer*>("gTimer")->stop();




    /**
    *Mark that the game is paused
    */
    is_playing = false;



}




void GLController::Unpause()
{


    /**
    *Start the main timer
    */
    if (findChild<QTimer*>("gTimer"))
        findChild<QTimer*>("gTimer")->start();



    /**
    *Mark that the game is playing
    */
    is_playing = true;



}




void GLController::SetPlaying(const bool &playing)
{


    /**
    *Pause and unpause as requested
    */
    if (playing == true)
        Unpause();
    else
        Pause();



}
