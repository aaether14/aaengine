#ifndef FBXMANAGER_H
#define FBXMANAGER_H



#include <QObject>
#include <QDebug>
#include <fbxsdk.h>
#include <GL/gl.h>




class FBXManager : public QObject
{


    Q_OBJECT
    FbxScene* mScene;


public:



    explicit FBXManager(QObject *parent = 0);
    void LoadFromFBX(const char * filename);



signals:




public slots:
};

#endif // FBXMANAGER_H
