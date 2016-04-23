#include <dialogs/console/logger.hpp>





QSharedPointer<Logger> Logger::m_instance;
QPointer<QTextEdit> Logger::m_textEdit;
qint64 Logger::m_message_counter = 0;






Logger* Logger::Instance()
{

    if (m_instance.isNull())
        m_instance.reset(new Logger);


    return m_instance.data();


}






void Logger::customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{


    Q_UNUSED(type)
    Q_UNUSED(context)



    if (m_message_counter > WIPE_AMOUNT)
    {
        m_message_counter = 0;
        m_textEdit->clear();
    }


    m_message_counter++;
    m_textEdit->append(msg);



}




void Logger::setTextEdit(QTextEdit * p_textEdit)
{

    m_textEdit = p_textEdit;



    if (!m_textEdit.isNull())
        qInstallMessageHandler(&Logger::customMessageHandler);


}




void Logger::InitializeOpenGLLogger()
{


    m_opengl_debug_logger = new QOpenGLDebugLogger(this);
    m_opengl_debug_logger->initialize();



    connect(m_opengl_debug_logger, &QOpenGLDebugLogger::messageLogged,
            this, &Logger::HandleOpenGLDebugMessage);



    m_opengl_debug_logger->startLogging();


}




Logger::~Logger()
{



    qInstallMessageHandler(0);



}



void Logger::HandleOpenGLDebugMessage(const QOpenGLDebugMessage &debugMessage)
{


    qDebug() << debugMessage;


}






