#include <script_module/jsconsole.hpp>





JSConsole::JSConsole(QObject *parent) : QObject(parent)
{

}




void JSConsole::log(QString msg)
{
    qDebug() << msg;
}
