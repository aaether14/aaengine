#include <fbx_manager/mesh.hpp>




void Mesh::RecursiveLoad(FbxNode *node, QOpenGLShaderProgram &shader, QString fbx_file_name)
{



    for (int i = 0; i < node->GetChildCount(); i++)
        RecursiveLoad(node->GetChild(i), shader, fbx_file_name);




    if(!node->GetNodeAttribute())
        return;
    FbxNodeAttribute::EType AttributeType = node->GetNodeAttribute()->GetAttributeType();
    if(AttributeType != FbxNodeAttribute::eMesh)
        return;





    FbxMesh * mesh = node->GetMesh();
    if (mesh->GetElementNormalCount() > 0 && mesh->GetElementUVCount() > 0)
        if (mesh->GetElementNormal(0)->GetMappingMode() != FbxGeometryElement::eByControlPoint ||
                mesh->GetElementUV(0)->GetMappingMode() != FbxGeometryElement::eByControlPoint)
        {
            mesh->SplitPoints();
            should_save_scene_after_load = true;
        }




    MeshEntry * new_mesh_entry = new MeshEntry();
    new_mesh_entry->LoadMesh(mesh, shader, fbx_file_name, &global_transform, texture_cache);
    mesh_entries.push_back(QSharedPointer<MeshEntry>(new_mesh_entry));






}




void Mesh::LoadTextures(FbxScene *scene)
{





}





Mesh::Mesh() : should_save_scene_after_load(false)
{

}




Mesh::~Mesh()
{



    delete texture_array;
    mesh_entries.clear();


}




void Mesh::LoadFromFBX(FBXManager *fbx_manager, QOpenGLShaderProgram &shader, const char *file_name)
{




    FbxImporter* importer = FbxImporter::Create(fbx_manager->GetManager(), "default_importer");
    bool importer_status = importer->Initialize(file_name, -1, fbx_manager->GetManager()->GetIOSettings());


    if(!importer_status)
    {
        qDebug() << "Call to FbxImporter::Initialize() failed";
        qDebug() << "Error returned: " << importer->GetStatus().GetErrorString();
        return;
    }



    FbxScene * scene = FbxScene::Create(fbx_manager->GetManager(), "default_scene");
    importer->Import(scene);
    importer->Destroy();




    LoadTextures(scene);



    FbxAxisSystem SceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
     if (SceneAxisSystem != FbxAxisSystem::OpenGL)
     {
         FbxAxisSystem::OpenGL.ConvertScene(scene);
     }



     FbxSystemUnit SceneSystemUnit = scene->GetGlobalSettings().GetSystemUnit();
     if( SceneSystemUnit.GetScaleFactor() != 1.0 )
     {
         FbxSystemUnit::cm.ConvertScene(scene);
     }





    FbxGeometryConverter geometry_converter(fbx_manager->GetManager());
    geometry_converter.Triangulate(scene, true);



    FbxNode * root_node = scene->GetRootNode();
    RecursiveLoad(root_node, shader, file_name);




    if (should_save_scene_after_load)
    {

        FbxExporter *exporter = FbxExporter::Create(fbx_manager->GetManager(), "default_exporter");
        bool exporter_status = exporter->Initialize(file_name, -1, fbx_manager->GetManager()->GetIOSettings());


        if(!exporter_status)
        {
            qDebug() << "Call to FbxExporter::Initialize() failed";
            qDebug() << "Error returned: " << exporter->GetStatus().GetErrorString();
            return;
        }


        exporter->Export(scene);
        exporter->Destroy();


    }





}

void Mesh::Draw(QOpenGLFunctions *f, QOpenGLShaderProgram &shader)
{


    for (auto it : mesh_entries)
        it->Draw(f, texture_cache, shader);



}
