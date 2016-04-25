#include <core/gl/glcontroller.hpp>






void GLController::keyPressEvent(QKeyEvent *e)
{


    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterKeyPress(e);


}





void GLController::keyReleaseEvent(QKeyEvent *e)
{

    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterKeyRelease(e);

}





void GLController::mousePressEvent(QMouseEvent *e)
{


    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMousePress(e);


}




void GLController::mouseReleaseEvent(QMouseEvent *e)
{


    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMouseRelease(e);



}




void GLController::mouseMoveEvent(QMouseEvent *e)
{

    if (findChild<InputRegister*>("gInput"))
        findChild<InputRegister*>("gInput")->RegisterMouseMovement(e);



}





void GLController::Pause()
{



    if (findChild<QTimer*>("gTimer"))
        findChild<QTimer*>("gTimer")->stop();



    if (findChild<QTimer*>("gBackupTimer"))
        findChild<QTimer*>("gBackupTimer")->start();




    is_playing = false;



}




void GLController::Unpause()
{



    if (findChild<QTimer*>("gTimer"))
        findChild<QTimer*>("gTimer")->start();



    if (findChild<QTimer*>("gBackupTimer"))
        findChild<QTimer*>("gBackupTimer")->stop();



    is_playing = true;



}




void GLController::SetPlaying(const bool &playing)
{



    if (playing == true)
        Unpause();
    else
        Pause();



}
