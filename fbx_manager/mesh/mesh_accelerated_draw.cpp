#include <fbx_manager/mesh/mesh.hpp>






void Mesh::AcceleratedDraw(QString material_name)
{




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    QVector<DrawElementsCommand> draw_commands;
    QVector<quint32> per_object_index;





    CacheDrawCommands(m_mesh_entries,
                      draw_commands,
                      per_object_index,
                      material_name);







    f->glBindBuffer( GL_DRAW_INDIRECT_BUFFER, m_gpu.indirect_buffer);
    f->glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsCommand) * draw_commands.size(), &draw_commands[0], GL_STATIC_DRAW );






    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(quint32) * per_object_index.size(), &per_object_index[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(MESH_PER_OBJECT_ATTRIBUTE_POINTER);
    f->glVertexAttribIPointer(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1, GL_UNSIGNED_INT, sizeof(quint32), 0);
    f->glVertexAttribDivisor(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1);





    f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0, draw_commands.size(), 0);




    draw_commands.clear();
    per_object_index.clear();




}







void Mesh::SendModelMatrixToShader()
{



    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();



    /**
     *the model matrix vector will be filled with the model matrices of the
     *mesh entries of the mesh
     */
    QVector<aae::mesh_util::float16> model_matrix;



    foreach(auto it, m_mesh_entries)
        model_matrix << aae::mesh_util::toFloat16((m_global_transform * it->GetLocalTransform()).constData());




    /**
    *Send the model matrices to the shader via ssbo binding
    */



    f->glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_gpu.ssbo);
    f->glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(aae::mesh_util::float16) * model_matrix.size(), &model_matrix[0], GL_STATIC_DRAW);
    f->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_gpu.ssbo);




    model_matrix.clear();



}










