#ifndef JSCONSOLE_H
#define JSCONSOLE_H




#include <QObject>
#include <QString>
#include <QDebug>





class JSConsole : public QObject
{
    Q_OBJECT


public:
    explicit JSConsole(QObject *parent = 0);


signals:


public slots:
    void log(QString msg);


};





#endif // JSCONSOLE_H
