#ifndef LOGGER_H
#define LOGGER_H



#include <QTextEdit>
#include <QPointer>




class Logger
{


public:


    static Logger* Instance();
    static void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    void setTextEdit(QTextEdit * p_textEdit);




private:



    Logger(){}
    Logger(Logger const&){}
    Logger& operator=(Logger const&){}



    static Logger* m_instance;
    static QPointer<QTextEdit> m_textEdit;




};




#endif // LOGGER_H
