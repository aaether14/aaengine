#include <fbx_manager/mesh.hpp>




void Mesh::RecursiveLoad(FbxNode * node,
                         QOpenGLShaderProgram &shader,
                         QVector<unsigned int> & master_indices,
                         QVector<float> & master_vertices,
                         QVector<float> &master_normals,
                         QVector<float> &master_uvs)
{




    for (int i = 0; i < node->GetChildCount(); i++)
        RecursiveLoad(node->GetChild(i),
                      shader,
                      master_indices,
                      master_vertices,
                      master_normals,
                      master_uvs);





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
                             master_uvs,
                             current_control_point_offset,
                             current_polygon_offset);




    mesh_entries.push_back(QSharedPointer<MeshEntry>(new_mesh_entry));




}




void Mesh::LoadMaterials(FbxScene *scene, QOpenGLShaderProgram &shader, QString fbx_file_name)
{





    for (int i = 0; i < scene->GetMaterialCount(); i++)
    {


        FbxSurfaceMaterial * material = scene->GetMaterial(i);
        if (material)
        {


            if (!materials.count(material->GetName()))
            {


                FbxProperty diffuse_prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);


                QVector3D diffuse_color(diffuse_prop.Get<FbxDouble3>().mData[0],
                        diffuse_prop.Get<FbxDouble3>().mData[1],
                        diffuse_prop.Get<FbxDouble3>().mData[2]);


                Material new_mat;
                new_mat.diffuse_color = diffuse_color;



                if(diffuse_prop.GetSrcObjectCount<FbxFileTexture>() > 0)
                {
                    FbxFileTexture * texture = diffuse_prop.GetSrcObject<FbxFileTexture>();
                    if (texture)
                    {
                        QString texture_index = ComputeTextureFilename(texture->GetFileName(), fbx_file_name);
                        if (QFileInfo(texture_index).exists())
                        {
                            if (!textures.count(texture_index))
                            {
                                textures[texture_index] = new QOpenGLTexture(QImage(texture_index).mirrored());
                            }
                            new_mat.difuse_texture_name = texture_index;
                            new_mat.use_diffuse_texture = true;
                        }

                    }
                }


                materials[material->GetName()] = new_mat;


            }

        }


    }




}





Mesh::Mesh() : should_save_scene_after_load(false),
    master_ibo(QOpenGLBuffer::IndexBuffer),
    master_vbo(QOpenGLBuffer::VertexBuffer),
    master_normals_vbo(QOpenGLBuffer::VertexBuffer),
    master_uvs_vbo(QOpenGLBuffer::VertexBuffer),
    current_control_point_offset(0),
    current_polygon_offset(0),
    ssbo(0),
    indirect_buffer(0)
{






}




Mesh::~Mesh()
{


    master_vao.destroy();
    master_ibo.destroy();
    master_vbo.destroy();
    master_normals_vbo.destroy();
    master_uvs_vbo.destroy();
    mesh_entries.clear();




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glDeleteBuffers(1, &indirect_buffer);
    f->glDeleteBuffers(1, &ssbo);



    qDeleteAll(textures);
    materials.clear();



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
    LoadMaterials(scene, shader, file_name);
    LoadBufferObjects(scene->GetRootNode(), shader);




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


    shader.setUniformValue("diffuse_texture", 0);



    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    master_vao.bind();



    QVector<float16> model_matrix;
    QVector<DrawElementsCommand> draw_commands;





    for (auto it : materials.keys())
    {



        for(int i = 0; i < mesh_entries.size(); i++)
        {


            if (mesh_entries[i]->DoesMaterialExist(it))
            {

                DrawElementsCommand c;
                c = mesh_entries[i]->GetDrawCommand(it);
                c.baseInstance = draw_commands.size();
                draw_commands << c;



                model_matrix << toFloat16((global_transform * mesh_entries[i]->GetLocalTransform()).constData());



            }



        }




        f->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        f->glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float16) * model_matrix.size(), &model_matrix[0], GL_DYNAMIC_DRAW);
        f->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);




        f->glBindBuffer( GL_DRAW_INDIRECT_BUFFER, indirect_buffer);
        f->glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsCommand) * draw_commands.size(), &draw_commands[0], GL_DYNAMIC_DRAW );



        f->glBindBuffer(GL_ARRAY_BUFFER, indirect_buffer);
        f->glEnableVertexAttribArray(2);
        f->glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(DrawElementsCommand), (GLvoid*)(4 * sizeof(GLuint)));
        f->glVertexAttribDivisor(2, 1);



        materials[it].SendToShader(shader);
        if (materials[it].use_diffuse_texture)
        textures[materials[it].difuse_texture_name]->bind();


        f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0, draw_commands.size(), 0);
        model_matrix.clear();
        draw_commands.clear();



        if (materials[it].use_diffuse_texture)
        textures[materials[it].difuse_texture_name]->release();


    }




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





    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glGenBuffers(1, &ssbo);
    f->glGenBuffers(1, &indirect_buffer);





    QVector<unsigned int> master_indices;
    QVector<float> master_vertices;
    QVector<float> master_normals;
    QVector<float> master_uvs;



    RecursiveLoad(root,
                  shader,
                  master_indices,
                  master_vertices,
                  master_normals,
                  master_uvs);


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



    master_uvs_vbo.create();
    master_uvs_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    master_uvs_vbo.bind();
    master_uvs_vbo.allocate(&master_uvs[0], sizeof(float) * master_uvs.size());


    shader.setAttributeArray("uv", GL_FLOAT, 0, 2);
    shader.enableAttributeArray("uv");



    master_vao.release();
    master_indices.clear();
    master_vertices.clear();
    master_normals.clear();
    master_uvs.clear();






}










