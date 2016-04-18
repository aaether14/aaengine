#include <core/inputregister.hpp>



InputRegister::InputRegister(QObject *parent) : QObject(parent)
{


    setObjectName("gInput");



    for (qint32 i = 0; i < 512; i++)
        keys[i] = 0;
    for (qint32 i = 0; i < 8; i++)
        buttons[i] = 0;


}



void InputRegister::RegisterKeyPress(QKeyEvent *e)
{

    qint32 key;
    if (e->key() > 512)
        key = (((unsigned long qint32) e->key()) & 0x000000FF) + 256;
    else
        key = e->key();


    keys[key]++;


}




void InputRegister::RegisterKeyRelease(QKeyEvent *e)
{

    qint32 key;
    if (e->key() > 512)
        key = (((unsigned long qint32) e->key()) & 0x000000FF) + 256;
    else
        key = e->key();


    keys[key] = 0;

}



void InputRegister::RegisterMousePress(QMouseEvent *e)
{

    if ((qint32)(e->button()) < 8)
        buttons[(qint32)(e->button())]++;


}




void InputRegister::RegisterMouseRelease(QMouseEvent *e)
{

    if ((qint32)(e->button()) < 8)
        buttons[(qint32)(e->button())] = 0;

}



void InputRegister::RegisterMouseMovement(QMouseEvent *e)
{


    mouse_position = QVector2D(e->pos());


}



bool InputRegister::getKey(qint32 key)
{

    if (key < 512)
        return keys[key] > 0;
    else
        return false;

}



bool InputRegister::getButton(qint32 button)
{

    if (button < 8)
        return buttons[button] > 0;
    else return false;

}



QVector2D InputRegister::getMousePosition()
{

    return mouse_position;

}





InputRegister::~InputRegister()
{



}
