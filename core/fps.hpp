#ifndef FPS_H
#define FPS_H




#include <QObject>
#include <QTime>





/**
 * @brief The FPS class is a basic fps computer
 */
class FPS : public QObject
{



    Q_OBJECT


    /**
     *@brief elapsed_timer is used to measure timer delta and compute fps from
     *it
     */
    QTime * elapsed_timer;
    /**
     *@brief frame_counter counts the number of frames that have passed from
     *the list timer rest
     */
    int frame_counter;
    /**
     * @brief fps is the final result
     */
    int fps;
    /**
     * @brief r_delta is the amount of msecs in a frame
     */
    float r_delta;




public:



    /**
     * @brief FPS will initialize timer
     * @param parent
     */
    explicit FPS(QObject *parent = 0);
    /**
      @brief will destroy timer
    */
    ~FPS();




signals:

    /**
     *@brief updatedFps sends the current fps
     */
    void updatedFps(int);


public slots:



    /**
     * @brief Update will compute fps
     */
    void Update();
    /**
     * @brief Get will return fps
     * @return fps
     */
    int Get();
    /**
     * @brief Delta will return r_delta
     * @return r_delta
     */
    float Delta();



public:



    Q_INVOKABLE int get() {return Get(); }



    Q_INVOKABLE float delta() {return Delta(); }




};

#endif // FPS_H
