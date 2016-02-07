#ifndef INPUTREGISTER_H
#define INPUTREGISTER_H



#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QVector2D>




class InputRegister : public QObject
{



    Q_OBJECT


    int keys[512];
    int buttons[8];
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
