#ifndef MESH_GPU_MEMORY_H
#define MESH_GPU_MEMORY_H




#include <QHash>
#include <QOpenGLFunctions_4_3_Core>







#define MESH_VERTEX_ATTRIBUTE_POINTER 0
#define MESH_PER_OBJECT_ATTRIBUTE_POINTER 1
#define MESH_NORMAL_ATTRIBUTE_POINTER 2
#define MESH_UV_ATTRIBUTE_POINTER 3
#define MESH_TANGENT_ATTRIBUTE_POINTER 4






/**
 *@brief The MeshGPUMemory struct will story all the gpu memory pointers
 *necesary for fbx mesh rendering
 */
struct MeshGPUMemory
{



    /**
     *@brief indirect_buffer_stride_cache stores the stride cache for each
     *material key
     */
    QHash<QString, quint32> indirect_buffer_stride_cache;
    /**
     *@brief indirect_buffer_size_cache stores the size cache for each material
     *key
     */
    QHash<QString, quint32> indirect_buffer_size_cache;
    /**
     *@brief per_object_buffer_stride_cache stores the per object buffer cache
     *for each material key
     */
    QHash<QString, quint32> per_object_buffer_stride_cache;


    /**
     * @brief vao will store the vertex array object id containing the buffers ids
     */
    GLuint vao;


    /**
     * @brief ssbo is used to pass per draw id model matrices to the shader
     */
    GLuint ssbo;
    /**
     *@brief indirect_buffer will store the command information for indirect
     *drawing in dynamic moder
     */
    GLuint indirect_buffer;
    /**
     *@brief per_object_buffer is needed to know which draw is the rasterizer
     *currently handling (dynamic mode)
     */
    GLuint per_object_buffer;



    /**
     *@brief cached_indirect_buffer will store the command information for
     *indirect drawing in cached mode
     */
    GLuint cached_indirect_buffer;
    /**
     *@brief cached_per_object_buffer is needed to know which draw is the
     *rasterizer currently handling (cached mode)
     */
    GLuint cached_per_object_buffer;



    /**
     *@brief master_vbo will store in the opengl memory the vertices of the
     *whole mesh
     */
    GLuint master_vbo;
    /**
     *@brief master_ibo will store in the opengl memory the indices of the
     *whole mesh
     */
    GLuint master_ibo;
    /**
     *@brief master_normals_vbo will store in the opengl memory the normals of
     *the whole mesh
     */
    GLuint master_normals_vbo;
    /**
     *@brief master_uvs_vbo will store in the opengl memory the uvs of the
     *whole mesh
     */
    GLuint master_uvs_vbo;
    /**
     *@brief master_tangents_vbo will store in the opengl memory the tangents
     *of the whole mesh
     */
    GLuint master_tangents_vbo;




};





/**
 * @brief ResetGPUMemory will reset the gpu memory pointers to default values
 * @param m_gpu
 */
inline void ResetGPUMemory(MeshGPUMemory & m_gpu)
{



    m_gpu.vao = 0;
    m_gpu.master_ibo = 0;
    m_gpu.master_vbo = 0;
    m_gpu.master_normals_vbo = 0;
    m_gpu.master_uvs_vbo = 0;
    m_gpu.master_tangents_vbo = 0;



    m_gpu.ssbo = 0;
    m_gpu.indirect_buffer = 0;
    m_gpu.per_object_buffer = 0;



    m_gpu.cached_indirect_buffer = 0;
    m_gpu.cached_per_object_buffer = 0;





}





/**
 * @brief ClearGPUMemory will clear gpu memory used by the mesh
 * @param m_gpu is the gpu memory struct
 * @param f is a pointer to opengl 4.3 functions
 */
inline void ClearGPUMemory(MeshGPUMemory & m_gpu,
                           QOpenGLFunctions_4_3_Core * f)
{



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



    m_gpu.indirect_buffer_stride_cache.clear();
    m_gpu.indirect_buffer_size_cache.clear();
    m_gpu.per_object_buffer_stride_cache.clear();



}




/**
 * @brief CreateVAO will create the vertex array object used by
 * the mesh and also bind certain buffers to it
 * @param m_gpu is the gpu memory struct
 * @param f is a pointer to opengl 4.3 functinos
 */
inline void CreateVAO(MeshGPUMemory & m_gpu,
                      QOpenGLFunctions_4_3_Core * f)
{



    /**
    *First generate the vertex array object and bind it to context
    */
    f->glGenVertexArrays(1, &m_gpu.vao);
    f->glBindVertexArray(m_gpu.vao);


    /**
    *Bind the index array
    */
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gpu.master_ibo);



    /**
    *Bind vertex array and setup shader pointer
    */
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_vbo);
    f->glEnableVertexAttribArray(MESH_VERTEX_ATTRIBUTE_POINTER);
    f->glVertexAttribPointer(MESH_VERTEX_ATTRIBUTE_POINTER, 3, GL_FLOAT, GL_FALSE, 0, 0);



    /**
    *Bind normal array and setup shader pointer
    */
    if (m_gpu.master_normals_vbo)
    {
        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_normals_vbo);
        f->glEnableVertexAttribArray(MESH_NORMAL_ATTRIBUTE_POINTER);
        f->glVertexAttribPointer(MESH_NORMAL_ATTRIBUTE_POINTER, 3, GL_FLOAT, GL_FALSE, 0, 0);

    }



    /**
    *Bind uv array and setup shader pointer
    */
    if (m_gpu.master_uvs_vbo)
    {

        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_uvs_vbo);
        f->glEnableVertexAttribArray(MESH_UV_ATTRIBUTE_POINTER);
        f->glVertexAttribPointer(MESH_UV_ATTRIBUTE_POINTER, 2, GL_FLOAT, GL_FALSE, 0, 0);

    }



    if (m_gpu.master_tangents_vbo)
    {

        f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.master_tangents_vbo);
        f->glEnableVertexAttribArray(MESH_TANGENT_ATTRIBUTE_POINTER);
        f->glVertexAttribPointer(MESH_TANGENT_ATTRIBUTE_POINTER, 4, GL_FLOAT, GL_FALSE, 0, 0);

    }




    f->glBindVertexArray(0);




}











#endif // MESH_GPU_MEMORY_H
