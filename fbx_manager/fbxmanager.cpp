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



    if (!dynamic_cast<MeshAsset*>(asset))
    {
        qDebug() << "FbxManager: Could not convert to MeshAsset!";
        return;
    }




    if(!static_cast<MeshAsset*>(asset)->isLoaded())
    {
        qDebug() << "FbxManager: MeshAsset not loaded!";
        return;
    }




    Mesh* mesh = static_cast<MeshAsset*>(asset)->GetMesh();
    ImportScene(file_name, mesh);



    mesh->LoadFromFBX(GetManager(),
                      file_name,


                      load_options.size() > 0 ? true : false,
                      load_options["convert_axis"].toBool(),


            load_options["convert_scale"].toBool(),
            load_options["split_points"].toBool(),
            load_options["generate_tangents"].toBool(),
            load_options["triangulate"].toBool(),
            load_options["convert_textures"].toBool());


}




BaseAsset *FBXManager::CreateAsset()
{


    return new MeshAsset();


}




void FBXManager::ImportScene(QString fbx_file_name,
                             Mesh * mesh)
{



    /**
     *First, create a fbx importer using the FbxManager
     */

    FbxImporter* importer = FbxImporter::Create(GetManager(), "Aaether Engine Importer");


    /**
     *Initialize importer on the mesh you want to load
     */

    bool importer_status = importer->Initialize(fbx_file_name.toStdString().c_str(),
                                                -1,
                                                GetManager()->GetIOSettings());


    /**
    *Catch any importer error that have might occured
    */

    if(!importer_status)
    {
        qDebug() << "Tried to load:" << fbx_file_name << "!";
        qDebug() << "Call to FbxImporter::Initialize() failed";
        qDebug() << "Error returned: " << importer->GetStatus().GetErrorString();
        qDebug() << "";
        return;
    }



    /**
     * Load the scene using the importer
     */


    FbxScene * scene = FbxScene::Create(GetManager(), "default_scene");
    importer->Import(scene);
    importer->Destroy();




    mesh->SetFbxScene(scene);




}













