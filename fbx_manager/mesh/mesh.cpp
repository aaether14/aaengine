#include <fbx_manager/mesh/mesh.hpp>







Mesh::Mesh():



    is_using_normals(false),
    is_using_uvs(false),
    is_using_tangents(false),



    should_save_scene_after_load(false),
    is_loaded(false),
    draw_method("cached")
{



    ResetGPUMemory(m_gpu);



}




Mesh::~Mesh()
{



    /**
     *Release gpu memory
     */



    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();





    if (m_gpu.vao)
        f->glDeleteVertexArrays(1, &m_gpu.vao);
    if (m_gpu.ssbo)
        f->glDeleteBuffers(1, &m_gpu.ssbo);



    if (m_gpu.indirect_buffer)
        f->glDeleteBuffers(1, &m_gpu.indirect_buffer);
    if(m_gpu.per_object_buffer)
        f->glDeleteBuffers(1, &m_gpu.per_object_buffer);




    if (m_gpu.cached_indirect_buffer)
        f->glDeleteBuffers(1, &m_gpu.cached_indirect_buffer);
    if (m_gpu.cached_per_object_buffer)
        f->glDeleteBuffers(1, &m_gpu.cached_per_object_buffer);




    if (m_gpu.master_vbo)
        f->glDeleteBuffers(1, &m_gpu.master_vbo);
    if (m_gpu.master_ibo)
        f->glDeleteBuffers(1, &m_gpu.master_ibo);
    if (m_gpu.master_normals_vbo)
        f->glDeleteBuffers(1, &m_gpu.master_normals_vbo);
    if (m_gpu.master_uvs_vbo)
        f->glDeleteBuffers(1, &m_gpu.master_uvs_vbo);
    if (m_gpu.master_tangents_vbo)
        f->glDeleteBuffers(1, &m_gpu.master_tangents_vbo);





    qDeleteAll(textures);
    qDeleteAll(mesh_entries);




    textures.clear();
    mesh_entries.clear();




    materials.clear();
    m_gpu.indirect_buffer_stride_cache.clear();
    m_gpu.indirect_buffer_size_cache.clear();
    m_gpu.per_object_buffer_stride_cache.clear();






}




void Mesh::LoadFromFBX(FbxManager *fbx_manager,
                       QString file_name,
                       bool normalize_scene,
                       bool convert_axis,
                       bool convert_scale,
                       bool split_points,
                       bool generate_tangents,
                       bool triangulate,
                       bool convert_textures)
{




    /**
     *First, create a fbx importer using the FbxManager
     */

    FbxImporter* importer = FbxImporter::Create(fbx_manager, "default_importer");


    /**
     *Initialize importer on the mesh you want to load
     */

    bool importer_status = importer->Initialize(file_name.toStdString().c_str(),
                                                -1,
                                                fbx_manager->GetIOSettings());


    /**
    *Catch any importer error that have might occured
    */

    if(!importer_status)
    {
        qDebug() << "Call to FbxImporter::Initialize() failed";
        qDebug() << "Error returned: " << importer->GetStatus().GetErrorString();
        return;
    }



    /**
     * Load the scene using the importer
     */


    FbxScene * scene = FbxScene::Create(fbx_manager, "default_scene");
    importer->Import(scene);
    importer->Destroy();




    /**
    *If requested, normalize the scene with the provided parameters
    */

    if(normalize_scene)
        NormalizeScene(scene, fbx_manager,
                       convert_axis,
                       convert_scale,
                       split_points,
                       generate_tangents,
                       triangulate,
                       convert_textures);




    /**
     *Load materials and buffer objects
     */

    LoadMaterials(scene, file_name);
    CommandLoadingBufferObjects(scene->GetRootNode());



    /**
    *If after load saving was requested, do so
    */


    if (should_save_scene_after_load)
    {


        /**
         *Initialize an exporter using the filename of the mesh
         */

        FbxExporter *exporter = FbxExporter::Create(fbx_manager, "Aaether Engine Exporter");



        bool exporter_status = exporter->Initialize(file_name.toStdString().c_str(),
                                                    -1,
                                                    fbx_manager->GetIOSettings());

        /**
        *Catch any error that might have occured during initialization
        */

        if(!exporter_status)
        {
            qDebug() << "Call to FbxExporter::Initialize() failed";
            qDebug() << "Error returned: " << exporter->GetStatus().GetErrorString();
            return;
        }


        /**
        *If everything went well, proceed to exporting the scene
        */

        exporter->Export(scene);
        exporter->Destroy();


    }







}








void Mesh::Draw(QOpenGLShaderProgram &shader)
{



    /**
    *If the mesh wasn't successfully loaded, don't bother to try drawing it
    */


    if (!is_loaded)
        return;



    /**
    Set the texture sampler for diffuse texture and also if the mesh is using
    tangents or not
    */

    shader.setUniformValue("diffuse_texture", 0);
    shader.setUniformValue("normal_map", 1);
    shader.setUniformValue("is_using_tangents", is_using_tangents);




    /**
     *get the current context function and bind the vertex array object of the
     *mesh
     */


    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glBindVertexArray(m_gpu.vao);



    /**
     *the model matrix vector will be filled with the model matrices of the
     *mesh entries of the mesh
     */
    QVector<float16> model_matrix;



    foreach(auto it, mesh_entries)
        model_matrix << toFloat16((global_transform * it->GetLocalTransform()).constData());




    /**
    *Send the model matrices to the shader via ssbo binding
    */



    f->glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_gpu.ssbo);
    f->glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float16) * model_matrix.size(), &model_matrix[0], GL_STATIC_DRAW);
    f->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_gpu.ssbo);




    model_matrix.clear();




    /**
    *For each material, depending on the draw method selected by the mesh,
    attempt to draw the model
    */




    foreach(auto it, materials.keys())
    {



        /**
        *Send material information to shader
        */



        materials[it].SendToShader(shader);


        if (materials[it].use_diffuse_texture)
            textures[materials[it].difuse_texture_name]->bind(0);


        if (materials[it].use_normal_map)
            textures[materials[it].normal_map_name]->bind(1);




        if (draw_method == "cached")
        {

            CachedDraw(it);

        }
        else if (draw_method == "accelerated")
        {

            AcceleratedDraw(it);

        }
        else
        {

            qDebug() << "Invalid draw method!";

        }



        if (materials[it].use_diffuse_texture)
            textures[materials[it].difuse_texture_name]->release(0);


        if (materials[it].use_normal_map)
            textures[materials[it].normal_map_name]->release(1);



    }





    /**
    *Unbind the vertex array object
    */

    f->glBindVertexArray(0);






}











