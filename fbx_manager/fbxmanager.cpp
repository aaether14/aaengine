#include <fbx_manager/fbxmanager.hpp>





FBXManager::FBXManager()
{




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








void FBXManager::Load(QString file_name, BaseAsset *asset)
{


    if(asset)
        if(static_cast<MeshAsset*>(asset)->isLoaded())
            static_cast<MeshAsset*>(asset)->GetMesh()->LoadFromFBX(GetManager(), file_name);


}









