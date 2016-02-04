#include <fbx_manager/fbxmanager.hpp>




FBXManager::FBXManager(QObject *parent) : QObject(parent)
{


    setObjectName("FBXManager");


    manager = FbxManager::Create();
    FbxIOSettings* io_settings = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(io_settings);




}




FBXManager::~FBXManager()
{

    manager->Destroy();
    mesh_entries.clear();

}






void FBXManager::LoadFromFBX(const char* file_name, QOpenGLShaderProgram & shader)
{





    FbxImporter* importer = FbxImporter::Create(GetManager(), "default_importer");
    bool initialised = importer->Initialize(file_name, -1, GetManager()->GetIOSettings());
    if(!initialised)
    {
        qDebug() << "Failed importer: " << file_name;
        return;
    }



    FbxScene * scene = FbxScene::Create(GetManager(), "default_scene");
    importer->Import(scene);
    importer->Destroy();





    FbxNode * root_node = scene->GetRootNode();
    for (int i = 0; i < root_node->GetChildCount(); i++)
    {



        FbxNode * current_node = root_node->GetChild(i);
        if(!current_node->GetNodeAttribute())
            continue;



        FbxNodeAttribute::EType AttributeType = current_node->GetNodeAttribute()->GetAttributeType();
        if(AttributeType != FbxNodeAttribute::eMesh)
            continue;




        FbxMesh * mesh = current_node->GetMesh();
        mesh->SplitPoints();



        MeshEntry * new_mesh_entry = new MeshEntry();
        new_mesh_entry->LoadMesh(mesh, shader);
        mesh_entries.push_back(QSharedPointer<MeshEntry>(new_mesh_entry));




    }





}



void FBXManager::Draw(QOpenGLFunctions *f)
{


    for (auto it : mesh_entries)
        it->Draw(f);



}






