#include <fbx_manager/mesh.hpp>




void Mesh::RecursiveLoad(FbxNode * node,
                         QOpenGLShaderProgram &shader,
                         QVector<unsigned int> & master_indices,
                         QVector<float> & master_vertices,
                         QVector<float> &master_normals)
{



    for (int i = 0; i < node->GetChildCount(); i++)
        RecursiveLoad(node->GetChild(i),
                      shader,
                      master_indices,
                      master_vertices,
                      master_normals);






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
    new_mesh_entry->LoadMesh(mesh,
                             master_indices,
                             master_vertices,
                             master_normals,
                             current_control_point_offset,
                             current_polygon_offset);



    mesh_entries.push_back(QSharedPointer<MeshEntry>(new_mesh_entry));






}




void Mesh::LoadTextures(FbxScene *scene, QOpenGLShaderProgram &shader, QString fbx_file_name)
{






}





Mesh::Mesh() : should_save_scene_after_load(false),
    master_ibo(QOpenGLBuffer::IndexBuffer),
    master_vbo(QOpenGLBuffer::VertexBuffer),
    master_normals_vbo(QOpenGLBuffer::VertexBuffer),
    current_control_point_offset(0),
    current_polygon_offset(0)
{

}




Mesh::~Mesh()
{


    master_vao.destroy();
    master_ibo.destroy();
    master_vbo.destroy();
    master_normals_vbo.destroy();
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





    NormalizeScene(scene, fbx_manager->GetManager());
    FbxNode * root_node = scene->GetRootNode();
    LoadBufferObjects(root_node, shader);




    if (should_save_scene_after_load)
    {

        FbxExporter *exporter = FbxExporter::Create(fbx_manager->GetManager(), "Aaether Engine Exporter");
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

void Mesh::Draw(QOpenGLShaderProgram &shader)
{



    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    master_vao.bind();


    QVector<GLsizei> count;
    QVector<GLvoid*> indices;
    QVector<QMatrix4x4> models;



    for (auto it : mesh_entries)
    {
        count << it->GetCount();
        indices << it->GetIndex();
        models << global_transform * mesh_entries[0]->GetLocalTransform();
    }



    GLuint ssbo;
    f->glGenBuffers(1, &ssbo);
    f->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    f->glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * 16 * mesh_entries.size(), &models[0], GL_STATIC_DRAW);
    f->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);




    f->glMultiDrawElements(GL_TRIANGLES, &count[0], GL_UNSIGNED_INT, &indices[0], mesh_entries.size());
    f->glDeleteBuffers(1, &ssbo);



    master_vao.release();




}






QString Mesh::ComputeTextureFilename(QString texture_name, QString fbx_file_name)
{


    QString texture_file_name;
    texture_name.replace("\\", "/");
    texture_name = texture_name.mid(texture_name.lastIndexOf("/") + 1, texture_name.length());




    QString directory;
    if (QString(fbx_file_name).lastIndexOf("/") > 0)
        directory = QString(fbx_file_name).mid(0, QString(fbx_file_name).lastIndexOf("/"));
    if (directory.length() > 0)
        texture_file_name = directory + "/" + texture_name;





    if (QFileInfo(texture_file_name).exists())
        return texture_file_name;
    else
    {
        texture_file_name = directory + "/" + QFileInfo(fbx_file_name).baseName() + ".fbm/" + texture_name;
        if (QFileInfo(texture_file_name).exists())
            return texture_file_name;
        else
            return "";
    }



}




void Mesh::NormalizeScene(FbxScene *scene, FbxManager *fbx_manager)
{



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




    FbxGeometryConverter geometry_converter(fbx_manager);
    geometry_converter.Triangulate(scene, true);



}




void Mesh::LoadBufferObjects(FbxNode *root, QOpenGLShaderProgram &shader)
{



    QVector<unsigned int> master_indices;
    QVector<float> master_vertices;
    QVector<float> master_normals;



    RecursiveLoad(root,
                  shader,
                  master_indices,
                  master_vertices,
                  master_normals);


    //creating vertex array object


    master_vao.create();
    master_vao.bind();


    //loading indices


    master_ibo.create();
    master_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    master_ibo.bind();
    master_ibo.allocate(&master_indices[0], sizeof(unsigned int) * master_indices.size());


    //loading vertices and binding shader attribute


    master_vbo.create();
    master_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    master_vbo.bind();
    master_vbo.allocate(&master_vertices[0], sizeof(float) * master_vertices.size());


    shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
    shader.enableAttributeArray("vertex");




    //loading normals and binding shader attribute

    master_normals_vbo.create();
    master_normals_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    master_normals_vbo.bind();
    master_normals_vbo.allocate(&master_normals[0], sizeof(float) * master_normals.size());


    shader.setAttributeArray("normal", GL_FLOAT, 0, 3);
    shader.enableAttributeArray("normal");



    master_vao.release();
    master_indices.clear();
    master_vertices.clear();
    master_normals.clear();






}










