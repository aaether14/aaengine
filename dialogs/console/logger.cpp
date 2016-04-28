#include <dialogs/console/logger.hpp>





QSharedPointer<Logger> Logger::m_instance;
QPointer<QTextEdit> Logger::m_console_output;
QSemaphore Logger::m_message_counter(0);






Logger* Logger::Instance()
{


    /**
    *If no singleton instance has yet been created, do so
    */
    if (m_instance.isNull())
        m_instance.reset(new Logger);


    /**
    *Return a pointer to the singleton instance
    */
    return m_instance.data();


}






void Logger::customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{



    /**
    *No use for this ATM so mark that they are unused to avoid compiler warnings
    */
    Q_UNUSED(type)
    Q_UNUSED(context)


    /**
    *If a sufficient amount of message have been recorded clear the console
    */
    if (m_message_counter.tryAcquire(WIPE_AMOUNT))
        m_console_output->clear();


    /**
    *Log the recived message to the console
    */
    m_message_counter.release();
    m_console_output->append(msg);



}




void Logger::SetConsoleOutputPointer(QTextEdit *p_console_output)
{


    /**
    *Set the pointer to the console output QTextEdit we want to log messages to
    */
    m_console_output = p_console_output;


    /**
    *If the console text edit is valid, redirect messages to it
    */
    if (!m_console_output.isNull())
        qInstallMessageHandler(&Logger::customMessageHandler);


}







#ifdef AAE_USING_OPENGL_DEBUG
void Logger::InitializeOpenGLLogger()
{


    /**
    *Create and initialize the opengl debug logger
    */
    m_opengl_debug_logger = new QOpenGLDebugLogger(this);
    m_opengl_debug_logger->initialize();



    /**
     *Each time opengl issues an error, log it
     */
    connect(m_opengl_debug_logger, &QOpenGLDebugLogger::messageLogged,
            this, &Logger::HandleOpenGLDebugMessage);



    /**
    *Start logging process
    */
    m_opengl_debug_logger->startLogging();


}
#endif





Logger::~Logger()
{


    /**
     *No longer redirect messages to in-game console
     */
    qInstallMessageHandler(0);


}



Logger::Logger()
{


#ifdef AAE_USING_OPENGL_DEBUG
    m_opengl_debug_logger = NULL;
#endif


}





#ifdef AAE_USING_OPENGL_DEBUG
void Logger::HandleOpenGLDebugMessage(const QOpenGLDebugMessage &debugMessage)
{

    /**
    *Print the message
    */
    qDebug() << debugMessage;


}
#endif





