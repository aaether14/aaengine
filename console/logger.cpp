#include <console/logger.hpp>




QSharedPointer<Logger> Logger::m_instance;
QPointer<QTextEdit> Logger::m_textEdit;





Logger* Logger::Instance()
{

    if (m_instance.isNull())
        m_instance.reset(new Logger);


    return m_instance.data();


}






void Logger::customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{

    m_textEdit->append(msg);

}




void Logger::setTextEdit(QTextEdit * p_textEdit)
{

    m_textEdit = p_textEdit;



    if (!m_textEdit.isNull())
        qInstallMessageHandler(&Logger::customMessageHandler);


}




Logger::~Logger()
{

    qInstallMessageHandler(0);

}



