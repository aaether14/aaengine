#include <fbx_manager/mesh/mesh.hpp>





void Mesh::CachedDraw(QOpenGLShaderProgram &shader,
                      QString material_name)
{




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    f->glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_gpu.cached_indirect_buffer);




    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.cached_per_object_buffer);
    f->glEnableVertexAttribArray(MESH_PER_OBJECT_ATTRIBUTE_POINTER);
    f->glVertexAttribIPointer(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1, GL_UNSIGNED_INT, sizeof(unsigned int), (GLvoid*)(sizeof(unsigned int) *
                                                                                                                     m_gpu.per_object_buffer_stride_cache.value(material_name)));
    f->glVertexAttribDivisor(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1);







    f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT,
                                   (GLvoid*)(sizeof(DrawElementsCommand)*m_gpu.indirect_buffer_stride_cache.value(material_name)),
                                   m_gpu.indirect_buffer_size_cache.value(material_name), 0);






}

