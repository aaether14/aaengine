#include <fbx_manager/mesh.hpp>






void Mesh::DynamicDraw(QOpenGLShaderProgram & shader,
                       QString material_name)
{




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    QVector<DrawElementsCommand> draw_commands;
    QVector<unsigned int> per_object_index;





    CacheDrawCommands(mesh_entries,
                      draw_commands,
                      per_object_index,
                      material_name);







    f->glBindBuffer( GL_DRAW_INDIRECT_BUFFER, indirect_buffer);
    f->glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsCommand) * draw_commands.size(), &draw_commands[0], GL_STATIC_DRAW );






    f->glBindBuffer(GL_ARRAY_BUFFER, per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * per_object_index.size(), &per_object_index[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(3);
    f->glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(unsigned int), 0);
    f->glVertexAttribDivisor(3, 1);





    materials[material_name].SendToShader(shader);






    if (materials[material_name].use_diffuse_texture)
        textures[materials[material_name].difuse_texture_name]->bind();




    f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0, draw_commands.size(), 0);




    draw_commands.clear();
    per_object_index.clear();





    if (materials[material_name].use_diffuse_texture)
        textures[materials[material_name].difuse_texture_name]->release();





}






