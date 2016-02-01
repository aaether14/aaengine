#include <console/logger.hpp>



Logger * Logger::m_instance = 0;
QPointer<QTextEdit> Logger::m_textEdit;




Logger* Logger::Instance()
{

    if (!m_instance)
        m_instance = new Logger;


    return m_instance;


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
