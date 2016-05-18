#include <fbx_manager/fbxmanager.hpp>





FBXManager::FBXManager()
{



#ifdef AAE_USING_FBX
    /**
    *Attempt to create the fbx manager
    */
    manager = FbxManager::Create();

    /**
    *Signal if fbx manager creation failed
    */
    if (!manager)
    {

        qDebug() << "Error: Unable to create Autodesk FBX SDK manager!";
        return;

    }
    else
    {
        /**
        *Output the sdk version and create io settings
        */
        qDebug() << "Autodesk FBX SDK version: " << manager->GetVersion();

        FbxIOSettings* io_settings = FbxIOSettings::Create(manager, IOSROOT);
        manager->SetIOSettings(io_settings);



    }
#endif



}





FBXManager::~FBXManager()
{


#ifdef AAE_USING_FBX
    /**
    *The fbx manager needs to be deinitialized
    */
    if (manager)
        manager->Destroy();
#endif


}








void FBXManager::Load(const QString &file_name,
                      BaseAsset *asset,
                      const QVariantMap &load_options)
{



    Q_UNUSED(load_options)



    /**
    *No asset reference provided mean there's no place to load the asset
    */
    if(!asset)
    {
        qDebug() << "FbxManager: No asset detected!";
        return;
    }


    /**
    *The provided asset must be a MeshAsset
    */
    if (!dynamic_cast<MeshAsset*>(asset))
    {
        qDebug() << "FbxManager: Could not convert to MeshAsset!";
        return;
    }



    /**
    *The MeshAsset has to have been initialized
    */
    if(!static_cast<MeshAsset*>(asset)->hasData())
    {
        qDebug() << "FbxManager: MeshAsset has no mesh data!";
        return;
    }



    /**
     *Get the mesh from the MeshAsset
     */
    Mesh* mesh = static_cast<MeshAsset*>(asset)->GetMesh();
    QFileInfo file_info(file_name);




    if (file_info.suffix() == "fbx")
    {
#ifdef AAE_USING_FBX
        /**
         *Import the scene from the fbx file and if everything went well import
         *mesh data from the scene
         */
        if (ImportScene(mesh, file_name))
        {
            mesh->LoadFromFbxFile(file_name);
            mesh->ReleaseFbxScene();
        }
#endif
    }
    else if (file_info.suffix() == "aaem")
    {

        /**
        *Import the mesh from an aaem file
        */
        mesh->LoadFromAAEMFile(file_name);
    }





}




BaseAsset *FBXManager::CreateAsset()
{

    /**
    *Create a new MeshAsset in the heap
    */
    return new MeshAsset();


}



#ifdef AAE_USING_FBX
bool FBXManager::ImportScene(Mesh * mesh,
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
        return false;
    }



    /**
     * Load the scene using the importer
     */
    mesh->SetFbxScene(FbxScene::Create(GetManager(), "default_scene"));
    importer->Import(mesh->GetScene());
    importer->Destroy();



    /**
    *Importing went well
    */
    return true;



}



void FBXManager::ExportScene(Mesh *mesh,
                             QString fbx_file_name)
{





    /**
    *Initialize an exporter using the filename of the mesh
    */

    FbxExporter *exporter = FbxExporter::Create(GetManager(), "Aaether Engine Exporter");


    /**
     *Initialize the exporter on the given file
     */
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
#endif












