#include <fbx_manager/mesh/mesh.hpp>





void Mesh::CachedDraw(const QString &material_name)
{




    /**
     * get opengl 4.3 functions from context
     */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    /**
    *Bind command buffer
    */
    f->glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_gpu.cached_indirect_buffer);



    /**
    *Bind helper buffer
    */
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.cached_per_object_buffer);
    f->glEnableVertexAttribArray(MESH_PER_OBJECT_ATTRIBUTE_POINTER);
    f->glVertexAttribIPointer(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1,
                              GL_UNSIGNED_INT,
                              sizeof(quint32),
                              (GLvoid*)(sizeof(quint32) * m_gpu.per_object_buffer_stride_cache.value(material_name)));
    f->glVertexAttribDivisor(MESH_PER_OBJECT_ATTRIBUTE_POINTER, 1);






    /**
    *Proceed to cached rendering
    */
    f->glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT,
                                   (GLvoid*)(sizeof(DrawElementsCommand)*m_gpu.indirect_buffer_stride_cache.value(material_name)),
                                   m_gpu.indirect_buffer_size_cache.value(material_name), 0);






}









void Mesh::CacheDrawCommands(QList<MeshEntry> &mesh_entries,
                             QVector<DrawElementsCommand> &draw_commands,
                             QVector<quint32> &per_object_index,
                             const QString &key)
{


    /**
    *Loop through mesh entries to extract draw commands
    */
    for(qint32 i = 0; i < mesh_entries.size(); i++)
    {

        /**
        *If the mesh entry has a draw command associated with the provided
        *material, extract it
        */
        if (mesh_entries[i].DoesMaterialExist(key))
        {



            DrawElementsCommand c;
            c = mesh_entries[i].GetDrawCommand(key);
            c.baseInstance = draw_commands.size();



            draw_commands << c;
            per_object_index << i;




        }

    }



}















