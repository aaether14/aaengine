#ifndef FPS_H
#define FPS_H




#include <QObject>
#include <QTime>




class FPS : public QObject
{



    Q_OBJECT
    QTime * elapsed_timer;
    int frame_counter;
    int fps;
    float r_delta;




public:
    explicit FPS(QObject *parent = 0);
    ~FPS();




signals:


public slots:
    void Update();
    int Get();
    float Delta();



public:
    Q_INVOKABLE int get() {return Get(); }
    Q_INVOKABLE float delta() {return Delta(); }




};

#endif // FPS_H
