#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H





#include <QQmlEngine>
#include <QPointer>
#include <QQmlComponent>
#include <QQmlContext>
#include <QMatrix4x4>
#include <QDebug>
#include <QTimer>
#include <QFileInfo>






class ScriptEngine : public QQmlEngine
{



    Q_OBJECT

    /**
     *@brief timer is a pointer to the timer that is used to update the scene,
     *it will be used to also update the script modules
     */
    QPointer<QTimer> timer;




public:


    /**
     * @brief ScriptEngine will register it self for script side use
     * @param parent
     */
    explicit ScriptEngine(QObject *parent = 0);

    /**
     * @brief ConnectToTimer will set the internal timer pointer to the provided one
     * @param new_timer is the new timer
     */
    void ConnectToTimer(QTimer * new_timer);



    Q_INVOKABLE void addQMLScript(QString path, bool has_update);



    Q_INVOKABLE void forceUpdate(QObject * obj);



signals:


public slots:


    void RunScriptFromString(QString script_code);


    void AddQMLScript(QString path, bool has_update);


    void AddQMLSingleton(QString path, QString def, QString name);


    void RegisterQObject(QObject * obj);


    /**
     * @brief LoadProject will load a certain object to the Settings QObject in the script engine
     * @param project_name is the name of the project to be loaded
     * @return will return true if it succefully loaded the project
     */
    bool LoadProject(QString project_name);



};

#endif // SCRIPTENGINE_H
