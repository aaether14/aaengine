#include <fbx_manager/mesh/mesh.hpp>






void Mesh::AcceleratedDraw(const QString &material_name)
{



    /**
     *Get opengl 4.3 functions from current context
     */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    /**
     *Will store draw commands here
     */
    QVector<aae::DrawElementsCommand> draw_commands;
    QVector<quint32> per_object_index;




    /**
     *Get draw commands of current material
     */
    CacheDrawCommands(m_mesh_entries,
                      draw_commands,
                      per_object_index,
                      material_name);






    /**
    *Upload data to draw commands buffer
    */
    f->glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_gpu.indirect_buffer);
    f->glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(aae::DrawElementsCommand) * draw_commands.size(), &draw_commands[0], GL_STATIC_DRAW);





    /**
    *Workaround to know shader-side which draw call we're appending
    */
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(quint32) * per_object_index.size(), &per_object_index[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(MESH_PER_OBJECT_ATTRIBUTE_POINTER);
    f->glVertexAttribIPointer(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1, GL_UNSIGNED_INT, sizeof(quint32), BUFFER_OFFSET(0));
    f->glVertexAttribDivisor(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1);




    /**
    *Draw mesh component
    */
    f->glMultiDrawElementsIndirect(GL_TRIANGLES,
                                   GL_UNSIGNED_INT,
                                   BUFFER_OFFSET(0),
                                   draw_commands.size(),
                                   0);




    /**
    *Clear some cache
    */
    draw_commands.clear();
    per_object_index.clear();




}







void Mesh::SendModelMatrixToShader()
{


    /**
     *Get opengl 4.3 functions from current context
     */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();



    /**
     *the model matrix vector will be filled with the model matrices of the
     *mesh entries of the mesh
     */
    QVector<aae::mesh_util::float16> model_matrix;



    /**
    *Constrcut the model matrices vector
    */
    foreach(auto it, m_mesh_entries)
        model_matrix << aae::mesh_util::toFloat16((m_global_transform * it.GetLocalTransform()).constData());




    /**
    *Send the model matrices to the shader via ssbo binding
    */
    f->glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_gpu.ssbo);
    f->glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(aae::mesh_util::float16) * model_matrix.size(), &model_matrix[0], GL_STATIC_DRAW);
    f->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_gpu.ssbo);




    /**
    *Clear some cache
    */
    model_matrix.clear();



}










