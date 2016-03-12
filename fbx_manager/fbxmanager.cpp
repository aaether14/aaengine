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








void FBXManager::Load(QString file_name,
                      BaseAsset *asset,
                      QVariantMap load_options)
{



    if(!asset)
    {
        qDebug() << "FbxManager: No asset detected!";
        return;
    }




    if(!static_cast<MeshAsset*>(asset)->isLoaded())
    {
        qDebug() << "FbxManager: MeshAsset not loaded!";
        return;
    }



    if (!dynamic_cast<MeshAsset*>(asset))
    {
        qDebug() << "FbxManager: Could not convert to MeshAsset!";
        return;
    }





    bool should_normalize = load_options.size() > 0 ? load_options["normalize"].toBool() : false;




    static_cast<MeshAsset*>(asset)->GetMesh()->LoadFromFBX(GetManager(),
                                                           file_name,
                                                           should_normalize);


}




BaseAsset *FBXManager::CreateAsset()
{


    return new MeshAsset();


}









