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
    int keys[512];
    /**
     *@brief buttons will be more than 0 if the mouse button is pressed
     */
    int buttons[8];
    /**
     *@brief mouse_position will store the mouse position relative to the
     *QOpenGLWidget (GLController)
     */
    QVector2D mouse_position;


public:


    explicit InputRegister(QObject *parent = 0);
    ~InputRegister();



    void RegisterKeyPress(QKeyEvent * e);
    void RegisterKeyRelease(QKeyEvent * e);
    void RegisterMousePress(QMouseEvent * e);
    void RegisterMouseRelease(QMouseEvent * e);
    void RegisterMouseMovement(QMouseEvent * e);



    Q_INVOKABLE bool getKey(int key);
    Q_INVOKABLE bool getButton(int button);
    Q_INVOKABLE QVector2D getMousePosition();




signals:




public slots:
};

#endif // INPUTREGISTER_H
