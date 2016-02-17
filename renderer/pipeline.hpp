#ifndef PIPELINE_H
#define PIPELINE_H




#include <QObject>
#include <QHash>
#include <QString>
#include <renderer/fbxrenderer.hpp>




class Pipeline : public QObject
{


    Q_OBJECT



    QHash<QString, BaseRenderer*> renderers;



    void AddRenderer(QString renderer_name, BaseRenderer* renderer);



public:
    explicit Pipeline(QObject *parent = 0);
    ~Pipeline();




signals:



public slots:


};

#endif // PIPELINE_H