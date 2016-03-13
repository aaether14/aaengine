#include <fbx_manager/fbxmanager.hpp>





FBXManager::FBXManager()
{




    manager = FbxManager::Create();




    if (!manager)
    {


        qDebug() << "Error: Unable to create Autodesk FBX SDK manager!";
        return;


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





    bool should_normalize = load_options.size() > 0 ? true : false;




    static_cast<MeshAsset*>(asset)->GetMesh()->LoadFromFBX(GetManager(),
                                                           file_name,
                                                           should_normalize,
                                                           load_options["convert_axis"].toBool(),
            load_options["convert_scale"].toBool(),
            load_options["split_points"].toBool(),
            load_options["generate_tangents"].toBool());


}




BaseAsset *FBXManager::CreateAsset()
{


    return new MeshAsset();


}









