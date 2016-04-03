#include <fbx_manager/mesh/mesh.hpp>







Mesh::Mesh():


    m_scene(NULL),


    is_using_normals(false),
    is_using_uvs(false),
    is_using_tangents(false),



    should_pass_geometry_to_opengl(false),
    should_pass_textures_to_opengl(false),



    has_loaded_geometry(false),
    has_loaded_textures(false),
    m_draw_method("cached")
{



    ResetGPUMemory(m_gpu);



}




Mesh::~Mesh()
{



    /**
     *Release gpu memory
     */



    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();





    if (m_gpu.vao)
        f->glDeleteVertexArrays(1, &m_gpu.vao);
    if (m_gpu.ssbo)
        f->glDeleteBuffers(1, &m_gpu.ssbo);



    if (m_gpu.indirect_buffer)
        f->glDeleteBuffers(1, &m_gpu.indirect_buffer);
    if(m_gpu.per_object_buffer)
        f->glDeleteBuffers(1, &m_gpu.per_object_buffer);




    if (m_gpu.cached_indirect_buffer)
        f->glDeleteBuffers(1, &m_gpu.cached_indirect_buffer);
    if (m_gpu.cached_per_object_buffer)
        f->glDeleteBuffers(1, &m_gpu.cached_per_object_buffer);




    if (m_gpu.master_vbo)
        f->glDeleteBuffers(1, &m_gpu.master_vbo);
    if (m_gpu.master_ibo)
        f->glDeleteBuffers(1, &m_gpu.master_ibo);
    if (m_gpu.master_normals_vbo)
        f->glDeleteBuffers(1, &m_gpu.master_normals_vbo);
    if (m_gpu.master_uvs_vbo)
        f->glDeleteBuffers(1, &m_gpu.master_uvs_vbo);
    if (m_gpu.master_tangents_vbo)
        f->glDeleteBuffers(1, &m_gpu.master_tangents_vbo);





    qDeleteAll(m_textures);
    qDeleteAll(m_mesh_entries);




    m_textures.clear();
    m_mesh_entries.clear();




    m_materials.clear();
    m_gpu.indirect_buffer_stride_cache.clear();
    m_gpu.indirect_buffer_size_cache.clear();
    m_gpu.per_object_buffer_stride_cache.clear();





}




void Mesh::Load(QString file_name)
{




    /**
     *Load materials and buffer objects
     */

    CommandLoadingMaterials(file_name);
    CommandLoadingBufferObjects();





}








void Mesh::Draw(QOpenGLShaderProgram &shader)
{




    /**
     *If the mesh has successfully computed geometry data but has not yet sent
     *it to opengl memory do so
     */


    if (should_pass_geometry_to_opengl)
    {
        PassGeometryDataToOpenGL();
        should_pass_geometry_to_opengl = false;
    }



    /**
    *If the mesh has successfully computed texture data but has not yet sent it
    *to opengl memory do so
    */


    if (should_pass_textures_to_opengl)
    {
        PassTextureDataToOpenGL();
        should_pass_textures_to_opengl = false;
    }




    /**
    *If the mesh wasn't successfully loaded, don't bother to try drawing it
    */


    if (!IsLoaded())
    {
        return;
    }
    else
    {
        QMutex mutex;
        mutex.lock();
        if (m_scene)
        {
            m_scene->Destroy();
            m_scene = NULL;
        }
        mutex.unlock();
    }




    /**
     *First send model matrices to shader
     */
    SendModelMatrixToShader();




    /**
    Set the texture sampler for diffuse texture and also if the mesh is using
    tangents or not
    */

    shader.setUniformValue("diffuse_texture", 0);
    shader.setUniformValue("normal_map", 1);
    shader.setUniformValue("is_using_tangents", is_using_tangents);




    /**
     * -----------------------------------------------------------------*/



    /**
     *get the current context function and bind the vertex array object of the
     *mesh
     */


    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glBindVertexArray(m_gpu.vao);




    /**
    *For each material, depending on the draw method selected by the mesh,
    attempt to draw the model
    */




    foreach(auto it, m_materials.keys())
    {



        /**
        *Send material information to shader
        */



        m_materials[it].SendToShader(shader);



        if (m_materials[it].use_diffuse_texture)
            if (m_textures[m_materials[it].difuse_texture_name])
                m_textures[m_materials[it].difuse_texture_name]->bind(0);



        if (m_materials[it].use_normal_map)
            if (m_textures[m_materials[it].normal_map_name])
                m_textures[m_materials[it].normal_map_name]->bind(1);




        if (m_draw_method == "cached")
        {

            CachedDraw(it);

        }
        else if (m_draw_method == "accelerated")
        {

            AcceleratedDraw(it);

        }
        else
        {

            qDebug() << "Invalid draw method!";

        }



        if (m_materials[it].use_diffuse_texture)
            if (m_textures[m_materials[it].difuse_texture_name])
                m_textures[m_materials[it].difuse_texture_name]->release(0);



        if (m_materials[it].use_normal_map)
            if (m_textures[m_materials[it].normal_map_name])
                m_textures[m_materials[it].normal_map_name]->release(1);



    }





    /**
    *Unbind the vertex array object
    */

    f->glBindVertexArray(0);






}











