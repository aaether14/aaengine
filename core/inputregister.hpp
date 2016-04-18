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
     * @brief keys will be more than 0 if the key is pressed
     */
    qint32 keys[512];
    /**
     *@brief buttons will be more than 0 if the mouse button is pressed
     */
    qint32 buttons[8];
    /**
     *@brief mouse_position will store the mouse position relative to the
     *QOpenGLWidget (GLController)
     */
    QVector2D mouse_position;


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
     * @param e
     */
    void RegisterKeyPress(QKeyEvent * e);
    /**
     * @brief RegisterKeyRelease - see glcontroller.hpp
     * @param e
     */
    void RegisterKeyRelease(QKeyEvent * e);
    /**
     * @brief RegisterMousePress - see glcontroller.hpp
     * @param e
     */
    void RegisterMousePress(QMouseEvent * e);
    /**
     * @brief RegisterMouseRelease - see glcontroller.hpp
     * @param e
     */
    void RegisterMouseRelease(QMouseEvent * e);
    /**
     * @brief RegisterMouseMovement - see glcontroller.hpp
     * @param e
     */
    void RegisterMouseMovement(QMouseEvent * e);



    Q_INVOKABLE bool getKey(qint32 key);
    Q_INVOKABLE bool getButton(qint32 button);
    Q_INVOKABLE QVector2D getMousePosition();




signals:




public slots:
};

#endif // INPUTREGISTER_H
