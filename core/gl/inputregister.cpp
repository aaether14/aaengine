#include <core/gl/inputregister.hpp>





InputRegister::InputRegister(QObject *parent) : QObject(parent)
{


    /**
     *Set the name of the QObject
     */
    setObjectName("gInput");



    /**
    *Clear the key and button arrays
    */
    for (qint32 i = 0; i < 512; i++)
        m_keys[i] = 0;
    for (qint32 i = 0; i < 8; i++)
        m_buttons[i] = 0;


}



void InputRegister::RegisterKeyPress(QKeyEvent *e)
{



    /**
     *Register a keypress in the key array
     */
    qint32 key;
    if (e->key() > 512)
        key = (((quint64) e->key()) & 0x000000FF) + 256;
    else
        key = e->key();


    m_keys[key]++;


}




void InputRegister::RegisterKeyRelease(QKeyEvent *e)
{

    /**
     *Register a key release in the key array
     */
    qint32 key;
    if (e->key() > 512)
        key = (((quint64) e->key()) & 0x000000FF) + 256;
    else
        key = e->key();


    m_keys[key] = 0;

}



void InputRegister::RegisterMousePress(QMouseEvent *e)
{


    /**
    *Register a mouse press in the mouse button array
    */
    if ((qint32)(e->button()) < 8)
        m_buttons[(qint32)(e->button())]++;


}




void InputRegister::RegisterMouseRelease(QMouseEvent *e)
{

    /**
    *Register a mouse release in the mouse button array
    */
    if ((qint32)(e->button()) < 8)
        m_buttons[(qint32)(e->button())] = 0;

}



void InputRegister::RegisterMouseMovement(QMouseEvent *e)
{

    /**
    *Register the mouse movement
    */
    m_mouse_position = QVector2D(e->pos());


}



bool InputRegister::getKey(const qint32 &key)
{


    /**
    *Query a certain key's activity
    */
    if (key < 512)
        return m_keys[key] > 0;
    else
        return false;

}



bool InputRegister::getButton(const qint32 &button)
{

    /**
    *Query a certain button's activity
    */
    if (button < 8)
        return m_buttons[button] > 0;
    else return false;

}



QVector2D InputRegister::getMousePosition()
{

    /**
    *Get the position of the cursor relative to the QOpenGLWidget
    */
    return m_mouse_position;

}





InputRegister::~InputRegister()
{


    /**
    *The glorious nothing...
    */



}
