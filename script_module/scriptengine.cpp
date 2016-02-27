#include <script_module/scriptengine.hpp>





ScriptEngine::ScriptEngine(QObject *parent) : QQmlEngine(parent)
{



    setObjectName("ScriptEngine");
    RegisterQObject(this);





}




void ScriptEngine::ConnectToTimer(QTimer *new_timer)
{


    timer = new_timer;


}







void ScriptEngine::addQMLScript(QString path, bool has_update)
{


    AddQMLScript(path, has_update);


}




void ScriptEngine::forceUpdate(QObject *obj)
{


    connect(timer, SIGNAL(timeout()), obj, SLOT(onUpdate()));


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





void ScriptEngine::AddQMLScript(QString path, bool has_update)
{


    QQmlComponent component(this, QUrl(path));
    QObject *obj = qobject_cast<QObject*>(component.create());
    obj->setParent(this);



    if(has_update)
    {
        if (!timer.isNull())
            forceUpdate(obj);
        else
            qDebug() << path << ": Could not set update procedure, no timer detected!";
    }



}




void ScriptEngine::AddQMLSingleton(QString path, QString def, QString name)
{


    qmlRegisterSingletonType(QUrl(path),
                             def.toStdString().c_str(),
                             1, 0,
                             name.toStdString().c_str());


}



void ScriptEngine::RegisterQObject(QObject *obj)
{


    rootContext()->setContextProperty(obj->objectName(), obj);


}





