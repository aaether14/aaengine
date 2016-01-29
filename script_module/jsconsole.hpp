#ifndef JSCONSOLE_H
#define JSCONSOLE_H

#include <QObject>

class JSConsole : public QObject
{
    Q_OBJECT
public:
    explicit JSConsole(QObject *parent = 0);

signals:

public slots:
};

#endif // JSCONSOLE_H