#include <core/inputregister.hpp>



InputRegister::InputRegister(QObject *parent) : QObject(parent)
{


    setObjectName("gInput");



    for (int i = 0; i < 512; i++)
        keys[i] = 0;
    for (int i = 0; i < 8; i++)
        buttons[i] = 0;


}



void InputRegister::RegisterKeyPress(QKeyEvent *e)
{

    int key;
    if (e->key() > 512)
        key = (((unsigned long int) e->key()) & 0x000000FF) + 256;
    else
        key = e->key();


    keys[key]++;


}




void InputRegister::RegisterKeyRelease(QKeyEvent *e)
{

    int key;
    if (e->key() > 512)
        key = (((unsigned long int) e->key()) & 0x000000FF) + 256;
    else
        key = e->key();


    keys[key] = 0;

}



void InputRegister::RegisterMousePress(QMouseEvent *e)
{

    if ((int)(e->button()) < 8)
        buttons[(int)(e->button())]++;


}




void InputRegister::RegisterMouseRelease(QMouseEvent *e)
{

    if ((int)(e->button()) < 8)
        buttons[(int)(e->button())] = 0;

}



void InputRegister::RegisterMouseMovement(QMouseEvent *e)
{


    mouse_position = QVector2D(e->pos());


}



bool InputRegister::getKey(int key)
{

    if (key < 512)
        return keys[key] > 0;

}



bool InputRegister::getButton(int button)
{

    if (button < 8)
        return buttons[button] > 0;

}



QVector2D InputRegister::getMousePosition()
{

    return mouse_position;

}



void InputRegister::setMousePosition(QVector2D position)
{

    mouse_position = position;

}



InputRegister::~InputRegister()
{



}
