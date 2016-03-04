#include <script_module/scriptengine.hpp>





ScriptEngine::ScriptEngine(QObject *parent) : QQmlEngine(parent)
{



    setObjectName("ScriptEngine");
    RegisterQObject(this);





}




ScriptEngine::~ScriptEngine()
{


    foreach(auto it, timer_connections)
        disconnect(it);


    timer_connections.clear();


}




void ScriptEngine::ConnectToTimer(QTimer *new_timer)
{


    if (new_timer)
        timer = new_timer;
    else
        qDebug() << "ScriptEngine: Invalid timer reference!";


}







void ScriptEngine::addQMLScript(QString path)
{


    AddQMLScript(path);


}




void ScriptEngine::forceUpdate(QJSValue value)
{


    timer_connections << connect(timer.data(), &QTimer::timeout, [=]() mutable
    {
        value.call();
    });


}




void ScriptEngine::RunScriptFromString(QString script_code)
{



    if (!findChild<QObject*>("Settings"))
    {
        qDebug() << "Settings object not found!";
        return;
    }



    QMetaObject::invokeMethod(findChild<QObject*>("Settings"),
                              "evaluate",
                              Qt::QueuedConnection,
                              Q_ARG(QVariant, script_code));


}





void ScriptEngine::AddQMLScript(QString path)
{



    QQmlComponent component(this, QUrl(path));



    if (!component.isReady() && component.isError())
    {
        qDebug() << path << " could not be loaded!";
        qDebug() << component.errors();
        return;
    }



    QObject *obj = qobject_cast<QObject*>(component.create());
    obj->setParent(this);




}






void ScriptEngine::RegisterQObject(QObject *obj)
{

    if (obj)
        rootContext()->setContextProperty(obj->objectName(), obj);
    else
        qDebug() << "ScriptEngine: Could not register QObject due to invalid reference!";


}




bool ScriptEngine::LoadProject(QString project_name)
{



    if (QFileInfo(project_name).exists())
        AddQMLScript(project_name);
    else
    {
        qDebug() << "Could not load settings at " << project_name << "!";
        return false;
    }


    return true;


}





