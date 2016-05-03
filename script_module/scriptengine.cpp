#include <script_module/scriptengine.hpp>





ScriptEngine::ScriptEngine(QObject *parent) : QQmlEngine(parent)
{



    /**
     *Set the name of the QObject
     */
    setObjectName("ScriptEngine");



    /**
     *Register the script engine to be accessable from the scripts
     */
    RegisterQObject(this);
    /**
     *Register the newly created game object
     */
    RegisterQObject(new GameObject(this));




}




ScriptEngine::~ScriptEngine()
{


   /**
   *The glorious nothing...
   */


}




void ScriptEngine::ConnectToTimer(QTimer *new_timer)
{


    /**
    *We need the timer that is used to know when to update the scene
    */
    if (new_timer)
        m_timer = new_timer;
    else
        qDebug() << "ScriptEngine: Invalid timer reference!";


}




void ScriptEngine::ResetGameObject()
{


    /**
     *Clear all the cache from the created components
     */
    clearComponentCache();


    /**
    *Delete any existing GameObject along with the script components
    */
    if (findChild<GameObject*>("GameObject"))
        delete findChild<GameObject*>("GameObject");


    /**
     *Register a newly created GameObject
     */
    RegisterQObject(new GameObject(this));








}







void ScriptEngine::addQMLScript(const QString &path)
{


    /**
     *First load the component
     */
    QQmlComponent component(this, QUrl(path));


    /**
    *If the component has not been loading correctly, log the error
    */
    if (!component.isReady() || component.isError())
    {
        qDebug() << path << " could not be loaded!";
        qDebug() << component.errors();
        return;
    }



    /**
     *Add the component to the game object
     */
    QObject *obj = qobject_cast<QObject*>(component.create());
    obj->setParent(findChild<GameObject*>("GameObject"));


}




void ScriptEngine::forceUpdate(QJSValue value)
{


    /**
    *If the argument is not a function, abort
    */
    if (!value.isCallable())
        return;


    /**
    *Connect the function to m_timer and register the connection
    */
    timer_connections << connect(m_timer.data(), &QTimer::timeout, [=]() mutable
    {
        value.call();
    });


}




void ScriptEngine::setWindowProperty(const QString &property_name,
                                     QVariant new_property)
{


    /**
    *Set a certain property of the MainController
    */
    parent()->setProperty(property_name.toStdString().c_str(), new_property);


}




void ScriptEngine::closeWindow()
{


    /**
    *Close the MainController
    */
    qobject_cast<QWidget*>(parent())->close();


}




QVariant ScriptEngine::getWindowProperty(const QString &property_name)
{


    /**
    *Query a certain window property from the MainController
    */
    return parent()->property(property_name.toStdString().c_str());


}





void ScriptEngine::RunScriptFromString(const QString &script_code)
{



    /**
    The evaluate function should be present in the Settings object, so first
    look for this object
    */
    if (!findChild<QObject*>("Settings"))
    {
        qDebug() << "Settings object not found!";
        return;
    }



    /**
     *If you can find the method, invoke it with the script_code argument
     */
    QMetaObject::invokeMethod(findChild<QObject*>("Settings"),
                              "evaluate",
                              Qt::QueuedConnection,
                              Q_ARG(QVariant, script_code));


}






void ScriptEngine::RegisterQObject(QObject *obj)
{


    /**
    *If the pointer to a QObject is valid than add it's reference to the root
    *context of the QML Engine
    */
    if (obj)
        rootContext()->setContextProperty(obj->objectName(), obj);
    else
        qDebug() << "ScriptEngine: Could not register QObject due to invalid reference!";


}




bool ScriptEngine::LoadProject(const QString &project_name)
{


    /**
    *If the file exits, load the project from it
    */
    if (QFileInfo(project_name).exists())
        addQMLScript(project_name);
    else
    {
        qDebug() << "Could not load settings at " << project_name << "!";
        return false;
    }


    return true;


}





