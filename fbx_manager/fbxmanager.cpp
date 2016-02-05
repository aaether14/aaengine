#include <fbx_manager/fbxmanager.hpp>




FBXManager::FBXManager(QObject *parent) : QObject(parent)
{


    setObjectName("FBXManager");



    manager = FbxManager::Create();


    if (!manager)
    {
        qDebug() << "Error: Unable to create Autodesk FBX SDK manager!";
    }
    else
    {
        qDebug() << "Autodesk FBX SDK version: " << manager->GetVersion();
        FbxIOSettings* io_settings = FbxIOSettings::Create(manager, IOSROOT);
        manager->SetIOSettings(io_settings);
    }




}




FBXManager::~FBXManager()
{

    manager->Destroy();

}






