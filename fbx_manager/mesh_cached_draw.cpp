#include <fbx_manager/mesh.hpp>





void Mesh::CachedDraw(QOpenGLShaderProgram &shader,
                      QString material_name)
{




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    f->glBindBuffer(GL_DRAW_INDIRECT_BUFFER, cached_indirect_buffer);




    f->glBindBuffer(GL_ARRAY_BUFFER, cached_per_object_buffer);
    f->glEnableVertexAttribArray(3);
    f->glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(unsigned int), (GLvoid*)(sizeof(unsigned int) *
                                                                                     per_object_buffer_stride_cache.value(material_name)));
    f->glVertexAttribDivisor(3, 1);






    materials[material_name].SendToShader(shader);




    if (materials[material_name].use_diffuse_texture)
        textures[materials[material_name].difuse_texture_name]->bind();




    f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT,
                                   (GLvoid*)(sizeof(DrawElementsCommand)*indirect_buffer_stride_cache.value(material_name)),
                                   indirect_buffer_size_cache.value(material_name), 0);





    if (materials[material_name].use_diffuse_texture)
        textures[materials[material_name].difuse_texture_name]->release();






}
