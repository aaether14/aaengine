#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H





#include <QQmlEngine>
#include <QPointer>
#include <QQmlComponent>
#include <QQmlContext>
#include <QMatrix4x4>
#include <QDebug>
#include <QTimer>






class ScriptEngine : public QQmlEngine
{



    Q_OBJECT


    QPointer<QTimer> timer;




public:


    explicit ScriptEngine(QObject *parent = 0);


    void ConnectToTimer(QTimer * new_timer);



    Q_INVOKABLE void addQMLScript(QString path, bool has_update);



    Q_INVOKABLE void forceUpdate(QObject * obj);



signals:


public slots:


    void RunScriptFromString(QString script_code);


    void AddQMLScript(QString path, bool has_update);


    void AddQMLSingleton(QString path, QString def, QString name);


    void RegisterQObject(QObject * obj);



};

#endif // SCRIPTENGINE_H
