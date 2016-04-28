#ifndef FPS_H
#define FPS_H




#include <QObject>
#include <QTime>





#define FPS_TIME_BETWEEN_COMPUTATIONS 100





/**
 * @brief The FPS class is a basic fps computer
 */
class FPS : public QObject
{



    Q_OBJECT


    /**
     *@brief m_elapsed_timer is used to measure timer delta and compute fps from
     *it
     */
    QTime * m_elapsed_timer;
    /**
     *@brief m_frame_counter counts the number of frames that have passed from
     *the list timer rest
     */
    qint32 m_frame_counter;
    /**
     * @brief fps is the final result
     */
    qint32 m_fps;
    /**
     * @brief m_delta is the amount of msecs in a frame
     */
    float m_delta;



    /**
     *@brief m_total_time is the time that has passed since the engine started (msecs)
     */
    static quint64 m_total_time;




public:



    /**
     * @brief FPS will initialize timer
     * @param parent is the parent of the QObject
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
    void updatedFps(qint32);


public slots:



    /**
     * @brief Update will compute fps
     */
    void Update();



public:



    /**
     * @brief GetTotalTime will return staticaly the the elapsed since game started in msecs
     * @return m_total_time
     */
    static inline quint64 GetTotalTime(){
        return m_total_time;
    }



    /**
     * @brief get will return fps
     * @return m_fps
     */
    Q_INVOKABLE qint32 get();

    /**
     * @brief delta will return r_delta
     * @return m_delta
     */
    Q_INVOKABLE float delta();


    /**
    * @brief totalTime will return time elapsed since game started in msecs
    * @return m_total_time
    */
    Q_INVOKABLE quint64 totalTime();




};

#endif // FPS_H
