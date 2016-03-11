#include <fbx_manager/mesh.hpp>







void Mesh::RecursiveLoad(FbxNode * node,
                         QVector<unsigned int> & master_indices,
                         QVector<float> & master_vertices,
                         QVector<float> &master_normals,
                         QVector<float> &master_uvs, QVector<float> &master_tangents)
{






    for (int i = 0; i < node->GetChildCount(); i++)
        RecursiveLoad(node->GetChild(i),
                      master_indices,
                      master_vertices,
                      master_normals,
                      master_uvs,
                      master_tangents);






    if(!node->GetNodeAttribute())
        return;





    FbxNodeAttribute::EType AttributeType = node->GetNodeAttribute()->GetAttributeType();
    if(AttributeType != FbxNodeAttribute::eMesh)
        return;




    FbxMesh * mesh = node->GetMesh();
    bool should_split = false;




    if (mesh->GetElementNormalCount() > 0)
        if (mesh->GetElementNormal(0)->GetMappingMode() != FbxGeometryElement::eByControlPoint)
            should_split = true;




    if (mesh->GetElementUVCount() > 0)
        if (mesh->GetElementUV(0)->GetMappingMode() != FbxGeometryElement::eByControlPoint)
            should_split = true;




    if (mesh->GetElementTangentCount() > 0)
        if (mesh->GetElementTangent(0)->GetMappingMode() != FbxGeometryElement::eByControlPoint)
            should_split = true;





    if (should_split)
    {
        mesh->SplitPoints();
        should_save_scene_after_load = true;
    }





    MeshEntry * new_mesh_entry = new MeshEntry();
    new_mesh_entry->LoadMesh(mesh,
                             master_indices,
                             master_vertices,
                             master_normals,
                             master_uvs,
                             master_tangents,
                             current_control_point_offset,
                             current_polygon_offset);




    mesh_entries << new_mesh_entry;




}








void Mesh::CacheDrawCommands(QList<MeshEntry *> &mesh_entries,
                             QVector<DrawElementsCommand> &draw_commands,
                             QVector<unsigned int> &per_object_index,
                             QString key)
{



    for(int i = 0; i < mesh_entries.size(); i++)
    {

        if (mesh_entries[i]->DoesMaterialExist(key))
        {

            DrawElementsCommand c;
            c = mesh_entries[i]->GetDrawCommand(key);
            c.baseInstance = draw_commands.size();
            draw_commands << c;


            per_object_index << i;


        }

    }



}





void Mesh::DynamicDraw(QOpenGLShaderProgram & shader,
                       QString material_name)
{



    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    QVector<unsigned int> per_object_index;
    QVector<DrawElementsCommand> draw_commands;







    CacheDrawCommands(mesh_entries,
                      draw_commands,
                      per_object_index,
                      material_name);







    f->glBindBuffer( GL_DRAW_INDIRECT_BUFFER, indirect_buffer);
    f->glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsCommand) * draw_commands.size(), &draw_commands[0], GL_STATIC_DRAW );






    f->glBindBuffer(GL_ARRAY_BUFFER, per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * per_object_index.size(), &per_object_index[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(4);
    f->glVertexAttribIPointer(4, 1, GL_UNSIGNED_INT, sizeof(unsigned int), 0);
    f->glVertexAttribDivisor(4, 1);





    materials[material_name].SendToShader(shader);
    if (materials[material_name].use_diffuse_texture)
        textures[materials[material_name].difuse_texture_name]->bind();




    f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0, draw_commands.size(), 0);
    draw_commands.clear();
    per_object_index.clear();





    if (materials[material_name].use_diffuse_texture)
        textures[materials[material_name].difuse_texture_name]->release();





}





void Mesh::CachedDraw(QOpenGLShaderProgram &shader,
                      QString material_name)
{




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    f->glBindBuffer(GL_ARRAY_BUFFER, cached_per_object_buffer);
    f->glEnableVertexAttribArray(4);
    f->glVertexAttribIPointer(4, 1,
                              GL_UNSIGNED_INT, sizeof(unsigned int),
                              (GLvoid*)(sizeof(unsigned int) * per_object_buffer_stride_cache.value(material_name)));
    f->glVertexAttribDivisor(4, 1);






    materials[material_name].SendToShader(shader);



    if (materials[material_name].use_diffuse_texture)
        textures[materials[material_name].difuse_texture_name]->bind();



    f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT,
                                   (GLvoid*)(sizeof(DrawElementsCommand)*indirect_buffer_stride_cache.value(material_name)),
                                   indirect_buffer_size_cache.value(material_name), 0);




    if (materials[material_name].use_diffuse_texture)
        textures[materials[material_name].difuse_texture_name]->release();






}






Mesh::Mesh() : vao(0),
    ssbo(0),
    indirect_buffer(0),
    per_object_buffer(0),
    master_vbo(0),
    master_ibo(0),
    master_normals_vbo(0),
    master_uvs_vbo(0),
    master_tangents_vbo(0),
    should_save_scene_after_load(false),
    current_polygon_offset(0),
    current_control_point_offset(0),
    is_loaded(false),
    draw_method("cached")
{






}




Mesh::~Mesh()
{





    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();



    if (vao)
        f->glDeleteVertexArrays(1, &vao);


    if (indirect_buffer)
        f->glDeleteBuffers(1, &indirect_buffer);
    if (ssbo)
        f->glDeleteBuffers(1, &ssbo);
    if (cached_indirect_buffer)
        f->glDeleteBuffers(1, &cached_indirect_buffer);
    if (cached_per_object_buffer)
        f->glDeleteBuffers(1, &cached_per_object_buffer);
    if(per_object_buffer)
        f->glDeleteBuffers(1, &per_object_buffer);
    if (master_vbo)
        f->glDeleteBuffers(1, &master_vbo);
    if (master_ibo)
        f->glDeleteBuffers(1, &master_ibo);
    if (master_normals_vbo)
        f->glDeleteBuffers(1, &master_normals_vbo);
    if (master_uvs_vbo)
        f->glDeleteBuffers(1, &master_uvs_vbo);
    if (master_tangents_vbo)
        f->glDeleteBuffers(1, &master_tangents_vbo);




    qDeleteAll(textures);
    qDeleteAll(mesh_entries);



    textures.clear();
    mesh_entries.clear();



    materials.clear();
    indirect_buffer_stride_cache.clear();
    indirect_buffer_size_cache.clear();
    per_object_buffer_stride_cache.clear();






}




void Mesh::LoadFromFBX(FbxManager *fbx_manager, QString file_name)
{




    FbxImporter* importer = FbxImporter::Create(fbx_manager, "default_importer");



    bool importer_status = importer->Initialize(file_name.toStdString().c_str(),
                                                -1,
                                                fbx_manager->GetIOSettings());



    if(!importer_status)
    {
        qDebug() << "Call to FbxImporter::Initialize() failed";
        qDebug() << "Error returned: " << importer->GetStatus().GetErrorString();
        return;
    }



    FbxScene * scene = FbxScene::Create(fbx_manager, "default_scene");
    importer->Import(scene);
    importer->Destroy();





    NormalizeScene(scene, fbx_manager);
    LoadMaterials(scene, file_name);
    LoadBufferObjects(scene->GetRootNode());




    if (should_save_scene_after_load)
    {

        FbxExporter *exporter = FbxExporter::Create(fbx_manager, "Aaether Engine Exporter");


        bool exporter_status = exporter->Initialize(file_name.toStdString().c_str(),
                                                    -1,
                                                    fbx_manager->GetIOSettings());


        if(!exporter_status)
        {
            qDebug() << "Call to FbxExporter::Initialize() failed";
            qDebug() << "Error returned: " << exporter->GetStatus().GetErrorString();
            return;
        }


        exporter->Export(scene);
        exporter->Destroy();


    }




    is_loaded = true;
    scene->Destroy();




}







void Mesh::Draw(QOpenGLShaderProgram &shader)
{



    if (!is_loaded)
        return;




    shader.setUniformValue("diffuse_texture", 0);




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glBindVertexArray(vao);




    QVector<float16> model_matrix;



    foreach(auto it, mesh_entries)
        model_matrix << toFloat16((global_transform * it->GetLocalTransform()).constData());




    f->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    f->glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float16) * model_matrix.size(), &model_matrix[0], GL_STATIC_DRAW);
    f->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);




    model_matrix.clear();






    foreach(auto it, materials.keys())
    {


        if (draw_method == "cached")
            CachedDraw(shader, it);
        else if (draw_method == "dynamic")
            DynamicDraw(shader, it);
        else
            qDebug() << "Invalid draw method!";


    }





    f->glBindVertexArray(0);






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
            return QString();



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










