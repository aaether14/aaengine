#include <script_module/gameobject.hpp>




GameObject::GameObject(QObject *parent) : QObject(parent)
{


    /**
     *Set the name of the QObject
     */
    setObjectName("GameObject");


}
