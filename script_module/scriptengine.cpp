#include <script_module/scriptengine.hpp>




ScriptEngine::ScriptEngine(QObject *parent) : QJSEngine(parent)
{


    setObjectName("ScriptEngine");
    globalObject().setProperty("console", newQObject(new JSConsole(this)));



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





