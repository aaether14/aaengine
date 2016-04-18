#include <fbx_manager/mesh/mesh.hpp>







Mesh::Mesh():



    m_scene(NULL),


    is_using_normals(false),
    is_using_uvs(false),
    is_using_tangents(false),



    has_loaded_geometry(false),
    has_loaded_textures(false),
    m_draw_method("cached")
{



    ResetGPUMemory(m_gpu);



}




Mesh::~Mesh()
{



    /**
     *Release gpu memory
     */



    ClearGPUMemory(m_gpu, QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>());




    qDeleteAll(m_textures);
    qDeleteAll(m_mesh_entries);



    m_textures.clear();
    m_mesh_entries.clear();
    m_materials.clear();






}




void Mesh::LoadFromFbxFile(QString file_name)
{




    /**
     *Load materials and buffer objects
     */

    FBX_CommandLoadingBufferObjects();
    FBX_CommandLoadingMaterials(file_name);





}








void Mesh::Draw(QOpenGLShaderProgram &shader)
{




    /**
    *If the mesh wasn't successfully loaded, don't bother to try drawing it
    */


    if (!IsLoaded())
        return;



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
            if (m_materials[it].textures.contains(i))
                if (m_textures[m_materials[it].textures[i]])
                    m_textures[m_materials[it].textures[i]]->bind(i);






        if (m_draw_method == "cached")
        {

            CachedDraw(it);

        }
        else if (m_draw_method == "accelerated")
        {

            AcceleratedDraw(it);

        }
        else
        {

            qDebug() << "Invalid draw method!";

        }




        for (qint32 i = 0; i < Material::number_of_texture_types; i++)
            if (m_materials[it].textures.contains(i))
                if (m_textures[m_materials[it].textures[i]])
                    m_textures[m_materials[it].textures[i]]->release(i);



    }





    /**
    *Unbind the vertex array object
    */

    f->glBindVertexArray(0);






}








