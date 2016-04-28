#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H





#include <QQmlEngine>
#include <QPointer>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QTimer>
#include <QFileInfo>



#include <script_module/gameobject.hpp>
#include <QWidget>




/**
 *@brief The ScriptEngine class will derive QQmlEngine and provide
 *functionality for script server hosting
 */
class ScriptEngine : public QQmlEngine
{



    Q_OBJECT

    /**
     *@brief timer is a pointer to the timer that is used to update the scene,
     *it will be used to also update the script modules
     */
    QPointer<QTimer> m_timer;




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



    /**
     * @brief ResetGameObject will reset the game object of the engine
     */
    void ResetGameObject();



    /**
    *@brief addQMLScript will add a certain QML script to the GameObject
    *@param path is the path of the script to add
    */
    Q_INVOKABLE void addQMLScript(const QString &path);



    /**
    *@brief forceUpdate will call a certain function each time the m_timer ticks
    *@param value is the function called
    */
    Q_INVOKABLE void forceUpdate(QJSValue value);


    /**
    *@brief setWindowProperty will set a certain property of the window
    *@param property_name is the name of property to be changed
    *@param new_property is the value that will update the chosen property
    */
    Q_INVOKABLE void setWindowProperty(const QString &property_name,
                                       QVariant new_property);


    /**
    *@brief closeWindow will close the MainController window
    */
    Q_INVOKABLE void closeWindow();


    /**
    *@brief getWindowProperty will return a property of the main window requested with
    * the property_name key
    *@param property_name is the name of the requested property
    */
    Q_INVOKABLE QVariant getWindowProperty(const QString &property_name);




signals:




public slots:


    /**
     * @brief RunScriptFromString will call evaluate function from Settings object
     * @param script_code is the code to be run
     */
    void RunScriptFromString(const QString &script_code);


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
    bool LoadProject(const QString &project_name);



};

#endif // SCRIPTENGINE_H
