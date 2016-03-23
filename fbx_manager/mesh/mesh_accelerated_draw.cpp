#include <fbx_manager/mesh/mesh.hpp>






void Mesh::AcceleratedDraw(QString material_name)
{




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    QVector<DrawElementsCommand> draw_commands;
    QVector<unsigned int> per_object_index;





    CacheDrawCommands(mesh_entries,
                      draw_commands,
                      per_object_index,
                      material_name);







    f->glBindBuffer( GL_DRAW_INDIRECT_BUFFER, m_gpu.indirect_buffer);
    f->glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsCommand) * draw_commands.size(), &draw_commands[0], GL_STATIC_DRAW );






    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * per_object_index.size(), &per_object_index[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(MESH_PER_OBJECT_ATTRIBUTE_POINTER);
    f->glVertexAttribIPointer(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1, GL_UNSIGNED_INT, sizeof(unsigned int), 0);
    f->glVertexAttribDivisor(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1);





    f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0, draw_commands.size(), 0);




    draw_commands.clear();
    per_object_index.clear();




}






