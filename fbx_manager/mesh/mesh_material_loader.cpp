#include <fbx_manager/mesh/mesh.hpp>







void Mesh::FBX_CommandLoadingMaterials(QString fbx_file_name)
{





    MaterialLoader * material_loader = new MaterialLoader(m_materials,
                                                          m_scene,
                                                          fbx_file_name);



    material_loader->Load();
    PassTextureDataToOpenGL();
    delete material_loader;






}





void Mesh::PassTextureDataToOpenGL()
{





    foreach(auto current_material, m_materials)
        foreach(auto current_texture, current_material.textures.values())
            if (!m_textures.contains(current_texture))
                m_textures[current_texture] = new QOpenGLTexture(QImage(current_texture).mirrored());




    /**
     * get opengl functions from context
     */

    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    /**
     * Handle command caching
     */


    QVector<DrawElementsCommand> cached_commands;
    QVector<quint32> cached_per_object_index;






    foreach(auto it, m_materials.keys())
    {




        QVector<DrawElementsCommand> commands;
        QVector<quint32> per_object_index;




        CacheDrawCommands(m_mesh_entries,
                          commands,
                          per_object_index,
                          it);




        m_gpu.indirect_buffer_stride_cache[it] = cached_commands.size();
        m_gpu.indirect_buffer_size_cache[it] = commands.size();
        m_gpu.per_object_buffer_stride_cache[it] = cached_per_object_index.size();




        cached_commands << commands;
        cached_per_object_index << per_object_index;





    }



    /**
    *Create and bind the vertex array object
    */


    if (!m_gpu.vao)
        f->glGenVertexArrays(1, &m_gpu.vao);
    f->glBindVertexArray(m_gpu.vao);




    f->glGenBuffers(1, &m_gpu.cached_indirect_buffer);
    f->glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_gpu.cached_indirect_buffer);
    f->glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsCommand) * cached_commands.size(), &cached_commands[0], GL_STATIC_DRAW);




    f->glGenBuffers(1, &m_gpu.cached_per_object_buffer);
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.cached_per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(quint32) * cached_per_object_index.size(), &cached_per_object_index[0], GL_STATIC_DRAW);





    cached_commands.clear();
    cached_per_object_index.clear();




    f->glBindVertexArray(0);
    has_loaded_textures = true;





}




