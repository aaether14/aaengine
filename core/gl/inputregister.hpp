#ifndef INPUTREGISTER_H
#define INPUTREGISTER_H



#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QVector2D>




/**
 *@brief The InputRegister class will register input events in a form they can
 *be transmitted to script
 */
class InputRegister : public QObject
{



    Q_OBJECT

    /**
     * @brief m_keys will be more than 0 if the key is pressed
     */
    qint32 m_keys[512];
    /**
     *@brief m_buttons will be more than 0 if the mouse button is pressed
     */
    qint32 m_buttons[8];
    /**
     *@brief m_mouse_position will store the mouse position relative to the
     *QOpenGLWidget (GLController)
     */
    QVector2D m_mouse_position;


public:


    /**
     * @brief InputRegister - basic constructor
     * @param parent
     */
    explicit InputRegister(QObject *parent = 0);
    /**
    *@brief ~InputRegister - basic destructor
    */
    ~InputRegister();


    /**
     * @brief RegisterKeyPress - see glcontroller.hpp
     * @param e is the event that will be processed
     */
    void RegisterKeyPress(QKeyEvent * e);
    /**
     * @brief RegisterKeyRelease - see glcontroller.hpp
     * @param e is the event that will be processed
     */
    void RegisterKeyRelease(QKeyEvent * e);
    /**
     * @brief RegisterMousePress - see glcontroller.hpp
     * @param e is the event that will be processed
     */
    void RegisterMousePress(QMouseEvent * e);
    /**
     * @brief RegisterMouseRelease - see glcontroller.hpp
     * @param e is the event that will be processed
     */
    void RegisterMouseRelease(QMouseEvent * e);
    /**
     * @brief RegisterMouseMovement - see glcontroller.hpp
     * @param e is the event that will be processed
     */
    void RegisterMouseMovement(QMouseEvent * e);


    /**
    *@brief getKey will query a certain key's activity
    *@param key is the key to be queried
    *@return true if key is currently pressed
    */
    Q_INVOKABLE bool getKey(const qint32 &key);
    /**
    *@brief getButton will query a certain button's activity
    *@param is the button to be queried
    *@param true if the button is currently pressed
    */
    Q_INVOKABLE bool getButton(const qint32 &button);
    /**
    *@brief getMousePosition will return the current mouse position of the mouse
    *relative to the QOpenGLWidget
    *@return m_mouse_position
    */
    Q_INVOKABLE QVector2D getMousePosition();




signals:




public slots:
};

#endif // INPUTREGISTER_H
