#ifndef FBXMANAGER_H
#define FBXMANAGER_H



#include <QObject>
#include <QDebug>
#include <fbxsdk.h>





class FBXManager : public QObject
{



    Q_OBJECT
    FbxManager * manager;




public:



    explicit FBXManager(QObject *parent = 0);
    ~FBXManager();
    /**
    FBX manager
    */
    inline FbxManager * GetManager(){return manager; }



signals:




public slots:
};

#endif // FBXMANAGER_H
