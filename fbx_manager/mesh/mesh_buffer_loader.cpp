#include <fbx_manager/mesh/mesh.hpp>









void Mesh::CommandLoadingBufferObjects()
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



    QFuture<void> geometry_loading_procces = QtConcurrent::run(geometry_loader, &GeometryLoader::Load);
    Q_UNUSED(geometry_loading_procces)



    geometry_loader->connect(geometry_loader, &GeometryLoader::HasFinishedLoading, [=](){


        QMutex mutex;
        mutex.lock();
        should_pass_geometry_to_opengl = true;
        mutex.unlock();


        delete geometry_loader;



    });







}




void Mesh::PassGeometryDataToOpenGL()
{



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
    *Create and bind the vertex array object
    */


    if (!m_gpu.vao)
    {
        f->glGenVertexArrays(1, &m_gpu.vao);
        f->glBindVertexArray(m_gpu.vao);
    }



    /**
    *Load the indicies
    */

    f->glGenBuffers(1, &m_gpu.master_ibo);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gpu.master_ibo);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * d_master_indices.size(), &d_master_indices[0], GL_STATIC_DRAW);



    /**
    *load the vertices
    */




    f->glGenBuffers(1, &m_gpu.master_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_master_vertices.size(), &d_master_vertices[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(MESH_VERTEX_ATTRIBUTE_POINTER);
    f->glVertexAttribPointer(MESH_VERTEX_ATTRIBUTE_POINTER, 3, GL_FLOAT, GL_FALSE, 0, 0);



    /**
    *If the mesh has normals, load them
    */


    if (is_using_normals)
    {


        f->glGenBuffers(1, &m_gpu.master_normals_vbo);
        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_normals_vbo);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_master_normals.size(), &d_master_normals[0], GL_STATIC_DRAW);
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
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_master_uvs.size(), &d_master_uvs[0], GL_STATIC_DRAW);
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
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_master_tangents.size(), &d_master_tangents[0], GL_STATIC_DRAW);
        f->glEnableVertexAttribArray(MESH_TANGENT_ATTRIBUTE_POINTER);
        f->glVertexAttribPointer(MESH_TANGENT_ATTRIBUTE_POINTER, 4, GL_FLOAT, GL_FALSE, 0, 0);



    }





    d_master_indices.clear();
    d_master_vertices.clear();
    d_master_normals.clear();
    d_master_uvs.clear();
    d_master_tangents.clear();





    f->glBindVertexArray(0);




    has_loaded_geometry = true;



}

















