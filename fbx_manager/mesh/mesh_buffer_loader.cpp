#include <fbx_manager/mesh/mesh.hpp>






void Mesh::CheckLayersUsedByMesh(FbxScene *scene)
{




    /**
    *Loop through the meshes and see if the have normals, uvs, or tangents
    */


    for (int i = 0; i < scene->GetGeometryCount(); i++)
    {



        FbxMesh * current_mesh = FbxCast<FbxMesh>(scene->GetGeometry(i));



        if (!current_mesh)
            continue;



        if (current_mesh->GetElementNormalCount() > 0)
            is_using_normals = true;



        if (current_mesh->GetElementUVCount() > 0)
            is_using_uvs = true;




        if (current_mesh->GetElementTangentCount() > 0)
            is_using_tangents = true;




    }



    /**
    *If the mesh has uvs but no textures then we will not load the uv data
    */

    if (is_using_uvs && !scene->GetTextureCount() > 0)
        is_using_uvs = false;



    /**
    *If not even the tangent information is present on the mesh then exit
    */


    if (!is_using_tangents)
        return;



    is_using_tangents = false;


    /**
     *Otherwise, see if there are any bump maps inside the mesh
    */

    for (int i = 0; i < scene->GetMaterialCount(); i++)
    {



        if (!scene->GetMaterial(i))
            continue;



        FbxProperty normal_map_property = scene->GetMaterial(i)->FindProperty(FbxSurfaceMaterial::sNormalMap);



        if (normal_map_property.GetSrcObjectCount<FbxFileTexture>() > 0)
        {
            is_using_tangents = true;
            break;
        }




    }




}







void Mesh::LoadBufferObjects(FbxNode *root)
{



    /**
     *Check if the mesh is using normals, uvs or tangents
     */

    CheckLayersUsedByMesh(root->GetScene());



    /**
     * get opengl functions from context
     */

    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    /**
    *Generate buffers for ssbo, command buffer and per object buffer
    */

    f->glGenBuffers(1, &m_gpu.ssbo);
    f->glGenBuffers(1, &m_gpu.indirect_buffer);
    f->glGenBuffers(1, &m_gpu.per_object_buffer);




    /**
     *Create the lists that will be filled with mesh data
     */


    QVector<unsigned int> master_indices;
    QVector<float> master_vertices;
    QVector<float> master_normals;
    QVector<float> master_uvs;
    QVector<float> master_tangents;





    /**
     *Commence recursive load on all submeshes
     */


    RecursiveLoad(root,
                  master_indices,
                  master_vertices,
                  master_normals,
                  master_uvs,
                  master_tangents);






    /**
    *Create and bind the vertex array object
    */


    f->glGenVertexArrays(1, &m_gpu.vao);
    f->glBindVertexArray(m_gpu.vao);





    /**
    *Load the indicies
    */

    f->glGenBuffers(1, &m_gpu.master_ibo);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gpu.master_ibo);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * master_indices.size(), &master_indices[0], GL_STATIC_DRAW);



    /**
    *load the vertices
    */




    f->glGenBuffers(1, &m_gpu.master_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * master_vertices.size(), &master_vertices[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(MESH_VERTEX_ATTRIBUTE_POINTER);
    f->glVertexAttribPointer(MESH_VERTEX_ATTRIBUTE_POINTER, 3, GL_FLOAT, GL_FALSE, 0, 0);



    /**
    *If the mesh has normals, load them
    */


    if (is_using_normals)
    {


        f->glGenBuffers(1, &m_gpu.master_normals_vbo);
        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_normals_vbo);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * master_normals.size(), &master_normals[0], GL_STATIC_DRAW);
        f->glEnableVertexAttribArray(MESH_NORMAL_ATTRIBUTE_POINTER);
        f->glVertexAttribPointer(MESH_NORMAL_ATTRIBUTE_POINTER, 3, GL_FLOAT, GL_FALSE, 0, 0);


    }



    /**
    *If the mesh has uvs, load them
    */


    if (is_using_uvs)
    {


        f->glGenBuffers(1, &m_gpu.master_uvs_vbo);
        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_uvs_vbo);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * master_uvs.size(), &master_uvs[0], GL_STATIC_DRAW);
        f->glEnableVertexAttribArray(MESH_UV_ATTRIBUTE_POINTER);
        f->glVertexAttribPointer(MESH_UV_ATTRIBUTE_POINTER, 2, GL_FLOAT, GL_FALSE, 0, 0);



    }



    /**
    *If the mesh has tangents, load them
    */


    if (is_using_tangents)
    {



        f->glGenBuffers(1, &m_gpu.master_tangents_vbo);
        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_tangents_vbo);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * master_tangents.size(), &master_tangents[0], GL_STATIC_DRAW);
        f->glEnableVertexAttribArray(MESH_TANGENT_ATTRIBUTE_POINTER);
        f->glVertexAttribPointer(MESH_TANGENT_ATTRIBUTE_POINTER, 4, GL_FLOAT, GL_FALSE, 0, 0);



    }



    /**
    *Clear the data lists
    */

    master_indices.clear();
    master_vertices.clear();
    master_normals.clear();
    master_uvs.clear();
    master_tangents.clear();







    /**
     * Handle command caching
     */


    QVector<DrawElementsCommand> cached_commands;
    QVector<unsigned int> cached_per_object_index;






    foreach(auto it, materials.keys())
    {




        QVector<DrawElementsCommand> commands;
        QVector<unsigned int> per_object_index;




        CacheDrawCommands(mesh_entries,
                          commands,
                          per_object_index,
                          it);




        m_gpu.indirect_buffer_stride_cache[it] = cached_commands.size();
        m_gpu.indirect_buffer_size_cache[it] = commands.size();
        m_gpu.per_object_buffer_stride_cache[it] = cached_per_object_index.size();




        cached_commands << commands;
        cached_per_object_index << per_object_index;





    }







    f->glGenBuffers(1, &m_gpu.cached_indirect_buffer);
    f->glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_gpu.cached_indirect_buffer);
    f->glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsCommand) * cached_commands.size(), &cached_commands[0], GL_STATIC_DRAW);




    f->glGenBuffers(1, &m_gpu.cached_per_object_buffer);
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.cached_per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * cached_per_object_index.size(), &cached_per_object_index[0], GL_STATIC_DRAW);





    cached_commands.clear();
    cached_per_object_index.clear();





    f->glBindVertexArray(0);






}


