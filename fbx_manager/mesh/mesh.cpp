#include <fbx_manager/mesh/mesh.hpp>







Mesh::Mesh():


    #ifdef AAE_USING_FBX
    m_scene(NULL),
    #endif


    is_using_normals(false),
    is_using_uvs(false),
    is_using_tangents(false),



    m_loaded_semaphore(0),


    m_file_name(""),
    m_draw_method("cached")
{


    /**
     *Reset gpu pointers
     */
    ResetGPUMemory(m_gpu);



}




Mesh::~Mesh()
{



    /**
     *Release gpu memory
     */
    ClearGPUMemory(m_gpu, QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>());



    /**
     *Delete textures
     */
    qDeleteAll(m_textures);
    m_textures.clear();



    /**
    *Delete mesh entries and materials
    */
    m_mesh_entries.clear();
    m_materials.clear();






}



#ifdef AAE_USING_FBX
void Mesh::LoadFromFbxFile(const QString &fbx_file_name)
{



    /**
    *Set the name of the mesh
    */
    m_file_name = fbx_file_name;



    /**
     *Load materials and buffer objects
     */
    FBX_CommandLoadingBufferObjects();
    FBX_CommandLoadingMaterials();




    /**
   *Pass data to opengl memory
   */
    PassGeometryDataToOpenGL();
    PassTextureDataToOpenGL();



    /**
    *Signal successful loading
    */
    m_loaded_semaphore.release();





}
#endif





void Mesh::LoadFromAAEMFile(const QString &aaem_file_name)
{



    /**
    *Set the name of the mesh
    */
    m_file_name = aaem_file_name;



    /**
    *Try to load and signal if it succeded
    */
    QFutureWatcher<bool> *aaem_loaidng_watcher = new QFutureWatcher<bool>();
    QFuture<bool> aaem_loading_process = QtConcurrent::run(this, &Mesh::DeserializeAAEM, aaem_file_name);
    aaem_loaidng_watcher->connect(aaem_loaidng_watcher, &QFutureWatcher<bool>::finished, [=]{



        if (aaem_loaidng_watcher->result())
            AAEOpenGLWorkerThread::Instance()->GetThread()->enque_work([=](){


             /**
             *Pass data to opengl memory
             */
                PassGeometryDataToOpenGL();
                PassTextureDataToOpenGL();


             /**
             *Clear cache and signal successful loading
             */
                ClearGeometryData();
                m_loaded_semaphore.release();




            });



        delete aaem_loaidng_watcher;
    });
    aaem_loaidng_watcher->setFuture(aaem_loading_process);



}








void Mesh::Draw(QOpenGLShaderProgram &shader)
{





    /**
    *If the mesh has not yet been loaded, no point in trying to render
    */
    if (!IsLoaded())
        return;



    /**
    *If the vertex array object has not yet been created, go ahead and do it
    */
    if (!m_gpu.vao)
        CreateVAO(m_gpu, QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>());




    /**
         *First send model matrices to shader
         */
    SendModelMatrixToShader();




    /**
        Set the texture sampler for diffuse texture and also if the mesh is using
        tangents or not
        */

    shader.setUniformValue("diffuse_texture", 0);
    shader.setUniformValue("normal_map", 1);
    shader.setUniformValue("is_using_tangents", is_using_tangents);




    /**
         * -----------------------------------------------------------------*/




    /**
         *get the current context function and bind the vertex array object of the
         *mesh
         */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glBindVertexArray(m_gpu.vao);




    /**
        *For each material, depending on the draw method selected by the mesh,
        attempt to draw the model
        */
    foreach(auto it, m_materials.keys())
    {



        /**
            *Send material information to shader
            */
        m_materials[it].SendToShader(shader);



        for (qint32 i = 0; i < Material::number_of_texture_types; i++)
            if (m_materials[it].GetTextures().contains(i))
                if (m_textures[m_materials[it].GetTextures()[i]])
                    m_textures[m_materials[it].GetTextures()[i]]->bind(i);






        if (m_draw_method == "accelerated")
        {

            AcceleratedDraw(it);

        }



        for (qint32 i = 0; i < Material::number_of_texture_types; i++)
            if (m_materials[it].GetTextures().contains(i))
                if (m_textures[m_materials[it].GetTextures()[i]])
                    m_textures[m_materials[it].GetTextures()[i]]->release(i);



    }





    /**
        *Unbind the vertex array object
        */
    f->glBindVertexArray(0);






}








