#ifndef MESH_H
#define MESH_H





#include <QDebug>
#include <QOpenGLTexture>




#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>




#include <fbx_manager/mesh/mesh_gpu_memory.h>
#include <fbx_manager/mesh/geometryloader.hpp>
#include <fbx_manager/mesh/materialloader.hpp>





/**
 * @brief The Mesh class handles loading, normalizing and rendering of the fbx 3d meshes
 */
class Mesh
{



    /**
     *@brief m_scene is a pointer to fbx scene data
     */
    FbxScene * m_scene;



    /**
     * @brief mesh_entries is the list of individual mesh entries contained by the parent Mesh
     */
    QList<MeshEntry*> m_mesh_entries;


    /**
     * @brief textures stores the textures used by the mesh using their name as a key
     */
    QHash<QString, QOpenGLTexture*> m_textures;
    /**
     * @brief materials stores the materials used by the mesh using their name as a key
     */
    QHash<QString, Material> m_materials;






    /**
     *@brief m_gpu will hold the gpu memory pointers for entire mesh data
     */
    MeshGPUMemory m_gpu;




    /**
     * @brief CommandLoadingBufferObjects will start the thread where GeometryLoader will work
     */
    void CommandLoadingBufferObjects();



    /**
     * @brief PassGeometryDataToOpenGL will use the data harvested by GeometryLoader
     * and pass it to opengl data buffers
     */
    void PassGeometryDataToOpenGL();





    /**
     * @brief LoadMaterials will load the materials used by the mesh
     * @param fbx_file_name is needed to compute the texture filenames
     */
    void CommandLoadingMaterials(QString fbx_file_name);



    /**
     *@brief PassTextureDataToOpenGL will use the data harvested by
     *MaterialLoader and pass it to opengl memory
     */
    void PassTextureDataToOpenGL();




    /**
     * @brief CacheDrawCommands will cache the draw commands needed for rendering, it has optimising purposes
     * @param mesh_entries is the list of mesh entries that will give some of their data to create a per-material draw command
     * @param draw_commands is a reference to the draw command vector to be filled
     * @param per_object_index is a reference to the per object vector to be filled
     * @param key is the material key
     */
    void CacheDrawCommands(QList<MeshEntry *> &mesh_entries,
                           QVector<DrawElementsCommand> & draw_commands,
                           QVector<unsigned int> &per_object_index,
                           QString key);





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
     *@brief should_pass_geometry_to_opengl will be true if the mesh has
     *finished loading geometry data and now needs to send it to opengl memory
     */
    bool should_pass_geometry_to_opengl;


    /**
     *@brief should_pass_textures_to_opengl will be true if the mesh has
     *finished loading the texture data and now needs to send it to opengl
     *memory
     */
    bool should_pass_textures_to_opengl;



    /**
     *@brief has_loaded_geometry will be true if the mesh has successfully
     *loaded the geometry and passed the data to opengl
     */
    bool has_loaded_geometry;


    /**
     *@brief has_loaded_textures will be true if the mesh has successfully
     *loaded textures and passed the data to opengl
     */
    bool has_loaded_textures;



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
    void AcceleratedDraw(QString material_name);



    /**
     * @brief CachedDraw is usually faster than the DynamicDraw but it
     * can't do any frustum culling inside the mesh
     * @param shader is the shader used by the engine to render this kind of components
     * @param material_name determines which material based commands are we taking for this render
     */
    void CachedDraw(QString material_name);





    /**
     *@brief SendModelMatrixToShader will send the model matrices of the mesh
     *entries to the shader
     */
    void SendModelMatrixToShader();





    /**
     * @brief master_indices is the index array of the mesh
     */
    QVector<unsigned int> d_master_indices;
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
     * @brief images will hold texture information untill it's sent to shader
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
     * @brief Load loads the mesh from the fbx file
     * @param file_name is the name of the file to be loaded
     */
    void Load(QString file_name);






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
                        bool convert_axis,
                        bool convert_scale,
                        bool split_points,
                        bool generate_tangents,
                        bool triangulate,
                        bool convert_textures);






    /**
     * @brief SetGlobalTransform will set the global transform of the mesh
     * @param transform is the new transform
     */
    inline void SetGlobalTransform(QMatrix4x4 transform) {m_global_transform = transform; }
    /**
     * @brief SetDrawMethod will set the draw method for mesh rendering
     * @param method is the new draw method
     */
    inline void SetDrawMethod(QString method){m_draw_method = method; }


    /**
     * @brief GetScene will return the scene pointer of the model
     * @return is the requested scene
     */
    inline FbxScene * GetScene(){return m_scene; }


    /**
     * @brief SetFbxScene will set the scene pointer of the fbx model
     * @param scene is the scene pointer
     */
    inline void SetFbxScene(FbxScene * scene){m_scene = scene; }




    /**
     * @brief IsLoaded will return true if the mesh has been successfully loaded
     * @return
     */
    inline bool IsLoaded(){
        return has_loaded_geometry && has_loaded_textures;
    }



    /**
     * @brief Draw will draw the mesh to the scene
     * @param shader is the fbx rendering shader
     */
    void Draw(QOpenGLShaderProgram & shader);





};



#endif // MESH_H
