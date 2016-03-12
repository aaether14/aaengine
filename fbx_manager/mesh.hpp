#ifndef MESH_H
#define MESH_H





#include <QDebug>
#include <QOpenGLTexture>
#include <QImage>
#include <QFileInfo>




#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QList>



#include <fbx_manager/meshentry.hpp>




/**
 * @brief The Mesh class handles loading, normalizing and rendering of the fbx 3d meshes
 */
class Mesh
{



    /**
    @brief float16 is a typedef to the 16 float array, it is needed in order to
    convert QMatrix4x4 to something we can send to the shader
    */
    typedef struct float16 { float m[16]; } float16;
    /**
     * @brief toFloat16 converts a float array to float16 typedef
     * @param arr is the float data
     * @return returns the float16 block
     */
    float16 toFloat16(const float* arr){float16 v; memcpy(&v, arr, sizeof(float16)); return v;}



    /**
     * @brief mesh_entries is the list of individual mesh entries contained by the parent Mesh
     */
    QList<MeshEntry*> mesh_entries;


    /**
     * @brief textures stores the textures used by the mesh using their name as a key
     */
    QHash<QString, QOpenGLTexture*> textures;
    /**
     * @brief materials stores the materials used by the mesh using their name as a key
     */
    QHash<QString, Material> materials;




    /**
     *@brief indirect_buffer_stride_cache stores the stride cache for each
     *material key
     */
    QHash<QString, unsigned int> indirect_buffer_stride_cache;
    /**
     *@brief indirect_buffer_size_cache stores the size cache for each material
     *key
     */
    QHash<QString, unsigned int> indirect_buffer_size_cache;
    /**
     *@brief per_object_buffer_stride_cache stores the per object buffer cache
     *for each material key
     */
    QHash<QString, unsigned int> per_object_buffer_stride_cache;


    /**
     * @brief vao will store the vertex array object id containing the buffers ids
     */
    GLuint vao;


    /**
     * @brief ssbo is used to pass per draw id model matrices to the shader
     */
    GLuint ssbo;
    /**
     *@brief indirect_buffer will store the command information for indirect
     *drawing in dynamic moder
     */
    GLuint indirect_buffer;
    /**
     *@brief per_object_buffer is needed to know which draw is the rasterizer
     *currently handling (dynamic mode)
     */
    GLuint per_object_buffer;



    /**
     *@brief cached_indirect_buffer will store the command information for
     *indirect drawing in cached mode
     */
    GLuint cached_indirect_buffer;
    /**
     *@brief cached_per_object_buffer is needed to know which draw is the
     *rasterizer currently handling (cached mode)
     */
    GLuint cached_per_object_buffer;



    /**
     *@brief master_vbo will store in the opengl memory the vertices of the
     *whole mesh
     */
    GLuint master_vbo;
    /**
     *@brief master_ibo will store in the opengl memory the indices of the
     *whole mesh
     */
    GLuint master_ibo;
    /**
     *@brief master_normals_vbo will store in the opengl memory the normals of
     *the whole mesh
     */
    GLuint master_normals_vbo;
    /**
     *@brief master_uvs_vbo will store in the opengl memory the uvs of the
     *whole mesh
     */
    GLuint master_uvs_vbo;
    /**
     *@brief master_tangents_vbo will store in the opengl memory the tangents
     *of the whole mesh
     */
    GLuint master_tangents_vbo;



    /**
     * @brief ComputeTextureFilename will compute the filename of the texture
     * acording the where fbx meshes will look for their textures (.fbm folder
     * and .fbx folder)
     * @param texture_name is the name of the texture as
     * extracted from the fbx file
     * @param fbx_file_name is the name of the file
     * we are trying to load
     * @return will return the required texture filename to load the texture if
     * it can find the texture, otherwise null string
     */
    QString ComputeTextureFilename(QString texture_name, QString fbx_file_name);



    /**
     * @brief NormalizeScene will take care of the differences of scale and
     * orientation that can occur in the a fbx scene
     * @param scene is the fbx scene to be normalized
     * @param fbx_manager is the manager of the fbx sdk
     */
    void NormalizeScene(FbxScene * scene, FbxManager * fbx_manager);


    /**
     * @brief LoadBufferObjects will load the opengl memory from the fbx file
     * @param root is the root in the fbx scene
     */
    void LoadBufferObjects(FbxNode * root);



    /**
     * @brief RecursiveLoad will recursively look through all the nodes in the scene and load data acordingly
     * @param node is the current node we're looking into
     * @param master_indices is a reference to the index buffer which
     *  will be uploaded to the opengl memory
     * @param master_vertices is a reference to the vertex buffer which
     *  will be uploaded to the opengl memory
     * @param master_normals is a reference to the normal buffer which
     *  will be uploaded to the opengl memory
     * @param master_uvs is a reference to the uv buffer which
     *  will be uploaded to the opengl memory
     */
    void RecursiveLoad(FbxNode * node,
                       QVector<unsigned int> & master_indices,
                       QVector<float> & master_vertices,
                       QVector<float> & master_normals,
                       QVector<float> & master_uvs,
                       QVector<float> & master_tangents);



    /**
     * @brief LoadMaterials will load the materials used by the mesh
     * @param scene is the scene which has the info of the materials
     * @param fbx_file_name is needed to compute the texture filenames
     */
    void LoadMaterials(FbxScene * scene, QString fbx_file_name);




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
     * @brief global_transform is the global transform of the mesh
     */
    QMatrix4x4 global_transform;
    /**
     *@brief should_save_scene_after_load is used to know whether the fbx file
     *has been updated and needs to be saved
     */
    bool should_save_scene_after_load;



    /**
     *@brief current_polygon_offset is used to know how to fill the mesh entry
     *draw command
     */
    int current_polygon_offset;
    /**
     *@brief current_control_point_offset is used to know how to fill the mesh
     *entry draw command
     */
    int current_control_point_offset;


    /**
     * @brief is_loaded - know at any instance if we succesfully loaded the 3d model
     */
    bool is_loaded;
    /**
     *@brief draw_method will be used to determine the rendering method so we
     *get the best performance result of each individual mesh
     */
    QString draw_method;




    /**
     * @brief DynamicDraw will draw the scene computing the draw commands on the
     *  fly this will allow for kd tree frustum culling inside the mesh but will
     * also be a bit slow in some cases
     * @param shader is the shader used by the engine to render this kind of components
     * @param material_name determines which material based commands are we taking for this render
     */
    void DynamicDraw(QOpenGLShaderProgram & shader,
                     QString material_name);



    /**
     * @brief CachedDraw is usually faster than the DynamicDraw but it
     * can't do any frustum culling inside the mesh
     * @param shader is the shader used by the engine to render this kind of components
     * @param material_name determines which material based commands are we taking for this render
     */
    void CachedDraw(QOpenGLShaderProgram & shader,
                    QString material_name);





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
     * @brief LoadFromFBX loads the mesh from the fbx file
     * @param fbx_manager is the manager of the fbx sdk
     * @param normalize_scene will be set to true if you want to
     * normalize axis system, scene unit and generate tangent data
     * for the loaded mesh
     * @param file_name is the name of the file to be loaded
     */
    void LoadFromFBX(FbxManager * fbx_manager,
                     QString file_name,
                     bool normalize_scene);


    /**
     * @brief SetGlobalTransform will set the global transform of the mesh
     * @param transform is the new transform
     */
    inline void SetGlobalTransform(QMatrix4x4 transform) {global_transform = transform; }
    /**
     * @brief SetDrawMethod will set the draw method for mesh rendering
     * @param method is the new draw method
     */
    inline void SetDrawMethod(QString method){draw_method = method; }



    /**
     * @brief Draw will draw the mesh to the scene
     * @param shader is the fbx rendering shader
     */
    void Draw(QOpenGLShaderProgram & shader);





};



#endif // MESH_H
