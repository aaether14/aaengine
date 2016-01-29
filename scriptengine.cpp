#include <scriptengine.hpp>




ScriptEngine::ScriptEngine(QObject *parent) : QJSEngine(parent)
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
    else
        qDebug() << result.toString();



}





