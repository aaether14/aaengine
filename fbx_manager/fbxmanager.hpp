#ifndef FBXMANAGER_H
#define FBXMANAGER_H




#include <QObject>
#include <QDebug>
#include <fbxsdk.h>
#include <fbx_manager/mesh.hpp>





class FBXManager : public QObject
{



    Q_OBJECT
    FbxManager * manager;




public:



    explicit FBXManager(QObject *parent = 0);
    ~FBXManager();



    inline FbxManager * GetManager(){return manager; }





    void LoadMesh(Mesh * mesh, QString file_name);





signals:




public slots:
};

#endif // FBXMANAGER_H
