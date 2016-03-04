#ifndef LOGGER_H
#define LOGGER_H



#include <QTextEdit>
#include <QSharedPointer>
#include <QPointer>




/**
 *@brief The Logger class is singleton that upon creation will install a
 *message handler to redirect the normal console output to the provided text
 *edit and upon deletion will restore the intials state
 */
class Logger
{


public:


    /**
     * @brief Instance - basic singleton getter
     * @return
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
     * @brief setTextEdit will set the text edit that this
     * class will redirect the console output to
     * @param p_textEdit is a pointer to the required text edit
     */
    void setTextEdit(QTextEdit * p_textEdit);

    /**
    @brief ~Logger will restore the intial console state
    */
    ~Logger();


private:


    /**
     *@brief Logger is set to private to ensure there will only be a single
     *instance of this singleton
     */
    Logger(){}



    Q_DISABLE_COPY(Logger)



    /**
     * @brief m_instance is the instance of the singleton
     */
    static QSharedPointer<Logger> m_instance;
    /**
     *@brief m_textEdit is a pointer to the text edit the console output will
     *redirected to
     */
    static QPointer<QTextEdit> m_textEdit;




};




#endif // LOGGER_H
