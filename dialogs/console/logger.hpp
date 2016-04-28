#ifndef LOGGER_H
#define LOGGER_H



#include <aae_defines.hpp>



#include <QTextEdit>
#include <QSharedPointer>
#include <QSemaphore>
#include <QPointer>
#ifdef AAE_USING_OPENGL_DEBUG
#include <QOpenGLDebugLogger>
#endif




#define WIPE_AMOUNT 1000





/**
 *@brief The Logger class is singleton that upon creation will install a
 *message handler to redirect the normal console output to the provided text
 *edit and upon deletion will restore the intials state
 */
class Logger : public QObject
{


    Q_OBJECT



public:



    /**
     * @brief Instance - basic singleton getter
     * @return singleton instance
     */
    static Logger* Instance();

    /**
     * @brief customMessageHandler see class definition
     * @param type
     * @param context
     * @param msg
     */
    static void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);


    /**
     * @brief SetConsoleOutputPointer will set the pointer to the console output QTextEdit
     * where we will log the messages
     * @param p_console_output is a pointer to the console output we want to log messages to
     */
    void SetConsoleOutputPointer(QTextEdit * p_console_output);


#ifdef AAE_USING_OPENGL_DEBUG
    /**
     *@brief InitializeOpenGLLogger will initialize the logger that will listen
     *to opengl error server
     */
    void InitializeOpenGLLogger();
#endif


    /**
    @brief ~Logger will restore the intial console state
    */
    ~Logger();




private:


    /**
     *@brief Logger is set to private to ensure there will only be a single
     *instance of this singleton
     */
    Logger();



    Q_DISABLE_COPY(Logger)



    /**
     * @brief m_instance is the instance of the singleton
     */
    static QSharedPointer<Logger> m_instance;
    /**
     *@brief m_textEdit is a pointer to the text edit the console output will
     *redirected to
     */
    static QPointer<QTextEdit> m_console_output;



    /**
     *@brief m_message_counter will count how many messages have been written to
     *console since last wipe
     */
    static QSemaphore m_message_counter;



#ifdef AAE_USING_OPENGL_DEBUG
    /**
     *@brief m_opengl_debug_logger is a debug logger used to listen to opengl
     *error server
     */
    QOpenGLDebugLogger * m_opengl_debug_logger;
#endif




private slots:


#ifdef AAE_USING_OPENGL_DEBUG
    /**
     * @brief HandleOpenGLDebugMessage will output a debug message from opengl error message
     * @param debugMessage is the error message
     */
    void HandleOpenGLDebugMessage(const QOpenGLDebugMessage &debugMessage);
#endif




};




#endif // LOGGER_H
