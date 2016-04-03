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



    Q_UNUSED(load_options)



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




    if(!static_cast<MeshAsset*>(asset)->hasData())
    {
        qDebug() << "FbxManager: MeshAsset has no mesh data!";
        return;
    }




    Mesh* mesh = static_cast<MeshAsset*>(asset)->GetMesh();



    ImportScene(mesh, file_name);
    mesh->Load(file_name);




}




BaseAsset *FBXManager::CreateAsset()
{


    return new MeshAsset();


}




void FBXManager::ImportScene(Mesh * mesh,
                             QString fbx_file_name)
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



void FBXManager::ExportScene(Mesh *mesh,
                             QString fbx_file_name)
{





    /**
    *Initialize an exporter using the filename of the mesh
    */

    FbxExporter *exporter = FbxExporter::Create(GetManager(), "Aaether Engine Exporter");



    bool exporter_status = exporter->Initialize(fbx_file_name.toStdString().c_str(),
                                                -1,
                                                GetManager()->GetIOSettings());

    /**
        *Catch any error that might have occured during initialization
        */

    if(!exporter_status)
    {
        qDebug() << "Tried to export:" << fbx_file_name << "!";
        qDebug() << "Call to FbxExporter::Initialize() failed";
        qDebug() << "Error returned: " << exporter->GetStatus().GetErrorString();
        qDebug() << "";
        return;
    }


    /**
    *If everything went well, proceed to exporting the scene
    */

    exporter->Export(mesh->GetScene());
    exporter->Destroy();







}













