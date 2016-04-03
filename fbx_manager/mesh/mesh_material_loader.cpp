#include <fbx_manager/mesh/mesh.hpp>







void Mesh::CommandLoadingMaterials(QString fbx_file_name)
{





    MaterialLoader * material_loader = new MaterialLoader(m_materials,
                                                          d_images,
                                                          m_scene,
                                                          fbx_file_name);



    QFuture<void> material_loading_process = QtConcurrent::run(material_loader, &MaterialLoader::Load);
    Q_UNUSED(material_loading_process)



    material_loader->connect(material_loader, &MaterialLoader::HasLoadedMaterials, [=](){


        QMutex mutex;
        mutex.lock();
        should_pass_textures_to_opengl = true;
        mutex.unlock();


        delete material_loader;


    });





}





void Mesh::PassTextureDataToOpenGL()
{




    foreach(auto it, d_images.keys())
    {


        m_textures[it] = new QOpenGLTexture(d_images[it]);


    }



    d_images.clear();




    /**
     * get opengl functions from context
     */

    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    /**
     * Handle command caching
     */


    QVector<DrawElementsCommand> cached_commands;
    QVector<unsigned int> cached_per_object_index;






    foreach(auto it, m_materials.keys())
    {




        QVector<DrawElementsCommand> commands;
        QVector<unsigned int> per_object_index;




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
    {
        f->glGenVertexArrays(1, &m_gpu.vao);
        f->glBindVertexArray(m_gpu.vao);
    }




    f->glGenBuffers(1, &m_gpu.cached_indirect_buffer);
    f->glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_gpu.cached_indirect_buffer);
    f->glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsCommand) * cached_commands.size(), &cached_commands[0], GL_STATIC_DRAW);




    f->glGenBuffers(1, &m_gpu.cached_per_object_buffer);
    f->glBindBuffer(GL_ARRAY_BUFFER, m_gpu.cached_per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * cached_per_object_index.size(), &cached_per_object_index[0], GL_STATIC_DRAW);





    cached_commands.clear();
    cached_per_object_index.clear();




    f->glBindVertexArray(0);



    has_loaded_textures = true;





}




