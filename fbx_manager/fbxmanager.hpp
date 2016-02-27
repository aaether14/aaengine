#ifndef FBXMANAGER_H
#define FBXMANAGER_H




#include <QDebug>
#include <fbxsdk.h>
#include <assets/baseassetloader.hpp>
#include <assets/meshasset.hpp>





class FBXManager : public BaseAssetLoader
{



    FbxManager * manager;




public:



    FBXManager();
    ~FBXManager();



    inline FbxManager * GetManager(){return manager; }


    void Load(QString file_name, BaseAsset * asset);


    BaseAsset *CreateAsset();





};

#endif // FBXMANAGER_H
