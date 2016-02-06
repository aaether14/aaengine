#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H




#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QMatrix4x4>
#include <core/glcontroller.hpp>
#include <QDebug>





class ScriptEngine : public QQmlEngine
{


    Q_OBJECT



public:
    explicit ScriptEngine(QObject *parent = 0);


signals:


public slots:
    void RunScriptFromString(QString script_code);
    void AddQMLScript(QString path, QTimer * timer);
    void RegisterQObject(QObject * obj);



};

#endif // SCRIPTENGINE_H
