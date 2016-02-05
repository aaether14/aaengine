#ifndef FPS_H
#define FPS_H

#include <QObject>

class FPS : public QObject
{
    Q_OBJECT
public:
    explicit FPS(QObject *parent = 0);

signals:

public slots:
};

#endif // FPS_H