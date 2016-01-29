#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H



#include <QJSEngine>
#include <QString>
#include <QDebug>




class ScriptEngine : public QJSEngine
{
    Q_OBJECT



public:
    explicit ScriptEngine(QObject *parent = 0);

signals:


public slots:
    void RunScriptFromString(QString script_code);



};

#endif // SCRIPTENGINE_H
