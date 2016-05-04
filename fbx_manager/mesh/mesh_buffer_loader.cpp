#include <fbx_manager/mesh/mesh.hpp>








#ifdef AAE_USING_FBX
void Mesh::FBX_CommandLoadingBufferObjects()
{




    /**
     *Commence recursive load on all submeshes
     */
    GeometryLoader * geometry_loader = new GeometryLoader(m_mesh_entries,



                                                          d_master_indices,
                                                          d_master_vertices,
                                                          d_master_normals,
                                                          d_master_uvs,
                                                          d_master_tangents,


                                                          is_using_normals,
                                                          is_using_uvs,
                                                          is_using_tangents,



                                                          m_scene);



    geometry_loader->Load();
    delete geometry_loader;


}
#endif



void Mesh::PassGeometryDataToOpenGL()
{



    /**
     * get opengl 4.3 functions from context
     */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    /**
    *Generate buffers for ssbo, command buffer and per object buffer
    */
    f->glGenBuffers(1, &m_gpu.ssbo);
    f->glGenBuffers(1, &m_gpu.indirect_buffer);
    f->glGenBuffers(1, &m_gpu.per_object_buffer);





    /**
    *Load the indicies
    */
    f->glGenBuffers(1, &m_gpu.master_ibo);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gpu.master_ibo);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quint32) * d_master_indices.size(), &d_master_indices[0], GL_STATIC_DRAW);




    /**
    *load the vertices
    */
    f->glGenBuffers(1, &m_gpu.master_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_master_vertices.size(), &d_master_vertices[0], GL_STATIC_DRAW);



    /**
    *If the mesh has normals, load them
    */
    if (is_using_normals)
    {


        f->glGenBuffers(1, &m_gpu.master_normals_vbo);
        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_normals_vbo);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_master_normals.size(), &d_master_normals[0], GL_STATIC_DRAW);


    }



    /**
    *If the mesh has uvs, load them
    */
    if (is_using_uvs)
    {


        f->glGenBuffers(1, &m_gpu.master_uvs_vbo);
        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_uvs_vbo);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_master_uvs.size(), &d_master_uvs[0], GL_STATIC_DRAW);



    }



    /**
    *If the mesh has tangents, load them
    */
    if (is_using_tangents)
    {



        f->glGenBuffers(1, &m_gpu.master_tangents_vbo);
        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_tangents_vbo);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_master_tangents.size(), &d_master_tangents[0], GL_STATIC_DRAW);



    }







    /**
     * Handle command caching
     */
    QVector<DrawElementsCommand> cached_commands;
    QVector<quint32> cached_per_object_index;






    foreach(auto it, m_materials.keys())
    {




        QVector<DrawElementsCommand> commands;
        QVector<quint32> per_object_index;




        CacheDrawCommands(m_mesh_entries,
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
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(quint32) * cached_per_object_index.size(), &cached_per_object_index[0], GL_STATIC_DRAW);





    /**
    *Clear some cache
    */
    cached_commands.clear();
    cached_per_object_index.clear();









}




void Mesh::ClearGeometryData()
{



    d_master_indices.clear();
    d_master_vertices.clear();
    d_master_normals.clear();
    d_master_uvs.clear();
    d_master_tangents.clear();



}

















