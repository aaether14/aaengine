#include <script_module/scriptengine.hpp>




ScriptEngine::ScriptEngine(QObject *parent) : QQmlEngine(parent)
{



    setObjectName("ScriptEngine");




}




void ScriptEngine::RunScriptFromString(QString script_code)
{


    QJSValue result = evaluate(script_code);
    if (result.isError())

        qDebug()
                << "Uncaught exception at line"
                << result.property("lineNumber").toInt()
                << ":" << result.toString();



}



void ScriptEngine::AddQMLScript(QString path, QTimer * timer)
{


    QQmlComponent component(this, QUrl(path));
    QObject *obj = qobject_cast<QObject*>(component.create());
    obj->setParent(this);



    if(timer)
    {
       connect(timer, SIGNAL(timeout()), obj, SLOT(update()));
    }



}



void ScriptEngine::RegisterQObject(QObject *obj)
{


   rootContext()->setContextProperty(obj->objectName(), obj);


}





