#ifndef MESH_H
#define MESH_H



#include <aae_defines.hpp>
#include <opengl_worker/aaeopenglworkerthread.hpp>


#include <QDebug>
#include <QSemaphore>



#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QtConcurrent/QtConcurrent>



#include <fbx_manager/mesh/mesh_gpu_memory.h>
#include <fbx_manager/entry/meshentry.hpp>



#ifdef AAE_USING_FBX
#include <fbx_manager/mesh/loader/fbx_geometryloader.hpp>
#include <fbx_manager/mesh/loader/fbx_materialloader.hpp>
#endif




/**
 * @brief The Mesh class handles loading, normalizing and rendering of the fbx 3d meshes
 */
class Mesh
{



#ifdef AAE_USING_FBX
    /**
     *@brief m_scene is a pointer to fbx scene data
     */
    FbxScene * m_scene;
#endif


    /**
     * @brief mesh_entries is the list of individual mesh entries contained by the parent Mesh
     */
    QList<MeshEntry> m_mesh_entries;


    /**
     * @brief textures stores the textures used by the mesh using their name as a key
     */
    QHash<QString, GLuint> m_textures;
    /**
     * @brief materials stores the materials used by the mesh using their name as a key
     */
    QHash<QString, Material> m_materials;




    /**
     *@brief m_gpu will hold the gpu memory pointers for entire mesh data
     */
    MeshGPUMemory m_gpu;




#ifdef AAE_USING_FBX
    /**
     * @brief CommandLoadingBufferObjects will start the thread where GeometryLoader will work
     */
    void FBX_CommandLoadingBufferObjects();



    /**
     * @brief LoadMaterials will load the materials used by the mesh
     */
    void FBX_CommandLoadingMaterials();
#endif



    /**
     * @brief PassGeometryDataToOpenGL will use the data harvested by GeometryLoader
     * and pass it to opengl data buffers
     */
    void PassGeometryDataToOpenGL();




    /**
     *@brief PassTextureDataToOpenGL will use the data harvested by
     *MaterialLoader and pass it to opengl memory
     */
    void PassTextureDataToOpenGL();



    /**
     *Will load the textures specified by materials
     */
    void LoadTextures();



    /**
     * @brief CacheDrawCommands will cache the draw commands needed for rendering, it has optimising purposes
     * @param mesh_entries is the list of mesh entries that will give some of their data to create a per-material draw command
     * @param draw_commands is a reference to the draw command vector to be filled
     * @param per_object_index is a reference to the per object vector to be filled
     * @param key is the material key
     */
    void CacheDrawCommands(QList<MeshEntry> &mesh_entries,
                           QVector<DrawElementsCommand> & draw_commands,
                           QVector<quint32> &per_object_index,
                           const QString &key);





    /**
     *@brief is_using_normals will be true if the mesh is using normals for
     *rendering
     */
    bool is_using_normals;
    /**
     *@brief is_using_uvs will be true if the mesh is using uvs for rendering
     *(i.e has diffuse textures)
     */
    bool is_using_uvs;
    /**
     *@brief is_using_tangents will be true if the mesh using tangents for
     *rendering (i.e has bump maps)
     */
    bool is_using_tangents;




    /**
     *@brief m_loaded_semaphore will hold information about whether the
     * mesh has been successfully loaded or not
     */
    QSemaphore m_loaded_semaphore;


    /**
     *@brief m_file_name will store the name of the file from which we loaded
     *the mesh
     */
    QString m_file_name;



    /**
     *@brief draw_method will be used to determine the rendering method so we
     *get the best performance result of each individual mesh
     */
    QString m_draw_method;



    /**
     * @brief global_transform is the global transform of the mesh
     */
    QMatrix4x4 m_global_transform;




    /**
     * @brief AcceleratedDraw will draw the scene computing the draw commands on the
     *  fly this will allow for kd tree frustum culling inside the mesh but will
     * also be a bit slow in some cases
     * @param shader is the shader used by the engine to render this kind of components
     * @param material_name determines which material based commands are we taking for this render
     */
    void AcceleratedDraw(const QString &material_name);



    /**
     * @brief CachedDraw is usually faster than the DynamicDraw but it
     * can't do any frustum culling inside the mesh
     * @param shader is the shader used by the engine to render this kind of components
     * @param material_name determines which material based commands are we taking for this render
     */
    void CachedDraw(const QString &material_name);





    /**
     *@brief SendModelMatrixToShader will send the model matrices of the mesh
     *entries to the shader
     */
    void SendModelMatrixToShader();



    /**
     * @brief DeserializeAAEM will deserialize the mesh from an aaem file
     * @param file_name is the name of the file which holds the mesh data
     * @return will return true if nothing went wrong
     */
    bool DeserializeAAEM(const QString &file_name);



    /**
     * @brief master_indices is the index array of the mesh
     */
    QVector<quint32> d_master_indices;
    /**
     * @brief master_vertices is the vertex array of the mesh
     */
    QVector<float> d_master_vertices;
    /**
     * @brief master_normals is the normal array of the mesh
     */
    QVector<float> d_master_normals;
    /**
     * @brief master_uvs is the uv array of the mesh
     */
    QVector<float> d_master_uvs;
    /**
     * @brief master_tangents is the tangent array of the mesh
     */
    QVector<float> d_master_tangents;
    /**
     * @brief d_images is a hash containing mesh texture images
     */
    QHash<QString, QImage> d_images;





public:



    /**
     * @brief Mesh is a basic constructor initializing
     * some of the properties of the mesh
     */
    Mesh();
    /**
      @brief ~Mesh releases of the opengl memory used by the mesh
    */
    ~Mesh();



    /**
     * @brief LoadFromAAEMFile will load the mesh from an aaem file
     * @param aaem_file_name is the name of the file to be loaded
     */
    void LoadFromAAEMFile(const QString &aaem_file_name);



    /**
     *@brief ClearGeometryData will release the data where we stored geometry
     *information
     */
    void ClearGeometryData();



#ifdef AAE_USING_FBX
    /**
     * @brief Load loads the mesh from the fbx file
     * @param fbx_file_name is the name of the file to be loaded
     */
    void LoadFromFbxFile(const QString &fbx_file_name);



    /**
     * @brief NormalizeScene will make sure the mesh is in an
     * accepted form for the engine
     * @param fbx_manager is the manager of the fbx sdk
     * @param convert_axis will attempt to convert mesh axis
     * system to opengl one
     * @param convert_scale will attempt to convert mesh scale
     * system to engine's one
     * @param split_points will attepmt to split vertices so as
     * there are only per control point vertex atributes (i.e normal,
     * tanget etc.)
     * @param generate_tangent will attempt to generate tangents for the mesh
     * @param triangulate will attempt to triangulate the mesh
     * @param convert_textures will attempt to convert the textures
     * from tga to other format (i.e png)
     */
    void NormalizeScene(FbxManager * fbx_manager,
                        const bool &convert_axis,
                        const bool &convert_scale,
                        const bool &split_points,
                        const bool &generate_tangents,
                        const bool &triangulate,
                        const bool &convert_textures);
#endif





    /**
     * @brief SetGlobalTransform will set the global transform of the mesh
     * @param transform is the new transform
     */
    inline void SetGlobalTransform(const QMatrix4x4 &transform) {
        m_global_transform = transform;
    }


    /**
     * @brief SetDrawMethod will set the draw method for mesh rendering
     * @param method is the new draw method
     */
    inline void SetDrawMethod(const QString &method){
        m_draw_method = method;
    }



#ifdef AAE_USING_FBX
    /**
     * @brief GetScene will return the scene pointer of the model
     * @return is the requested scene
     */
    inline FbxScene * GetScene(){
        return m_scene;
    }


    /**
     * @brief SetFbxScene will set the scene pointer of the fbx model
     * @param scene is the scene pointer
     */
    inline void SetFbxScene(FbxScene * scene){
        m_scene = scene;
    }



    /**
     * @brief ReleaseFbxScene will release the memory used by the fbx data
     */
    inline void ReleaseFbxScene(){
        if (m_scene)
            m_scene->Destroy();
    }
#endif



    /**
     * @brief IsLoaded will return true if the mesh has been successfully loaded
     * @return true if the mesh is loaded
     */
    inline bool IsLoaded(){
        /**
        *This means it has successfully loaded both geometry and material data and this data
        * has also been sent to opengl memory
        */
        return m_loaded_semaphore.available();
    }




    inline const QString &GetFileName() const{
        return m_file_name;
    }



    /**
     * @brief Draw will draw the mesh to the scene
     * @param shader is the fbx rendering shader
     */
    void Draw(QOpenGLShaderProgram & shader);




    /**
     * @brief SerializeAAEM will serialize the mesh to an aaem file
     * @param file_name is the name of the new file which will hold
     * the mesh data
     */
    void SerializeAAEM(const QString &file_name);




};



#endif // MESH_H
