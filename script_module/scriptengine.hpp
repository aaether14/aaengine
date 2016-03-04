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




    /**
     *@brief timer_connections will store the timer connections to break them
     *upon reload
     */
    QList<QMetaObject::Connection> timer_connections;




public:


    /**
     * @brief ScriptEngine will register it self for script side use
     * @param parent
     */
    explicit ScriptEngine(QObject *parent = 0);
    /**
    @brief ~ScriptEngine will destroy any connections tied to the timer
    */
    ~ScriptEngine();

    /**
     * @brief ConnectToTimer will set the internal timer pointer to the provided one
     * @param new_timer is the new timer
     */
    void ConnectToTimer(QTimer * new_timer);




    Q_INVOKABLE void addQMLScript(QString path);



    Q_INVOKABLE void forceUpdate(QJSValue value);




signals:


public slots:


    /**
     * @brief RunScriptFromString will call evaluate function from Settings object
     * @param script_code is the code to be run
     */
    void RunScriptFromString(QString script_code);

    /**
     * @brief AddQMLScript will add a script to the QML context
     *  and parent it to the ScriptEngine
     * @param path is the path to the script
     */
    void AddQMLScript(QString path);


    /**
     * @brief RegisterQObject will register the object to the QML context
     * @param obj is the object to be registered
     */
    void RegisterQObject(QObject * obj);


    /**
     * @brief LoadProject will load a certain object to the Settings QObject in the script engine
     * @param project_name is the name of the project to be loaded
     * @return will return true if it succefully loaded the project
     */
    bool LoadProject(QString project_name);



};

#endif // SCRIPTENGINE_H
