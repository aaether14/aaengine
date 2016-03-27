#ifndef MESH_H
#define MESH_H





#include <QDebug>
#include <QOpenGLTexture>
#include <QImage>




#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QList>
#include <QThread>




#include <fbx_manager/mesh/mesh_gpu_memory.h>
#include <fbx_manager/mesh/geometryloader.hpp>





/**
 * @brief The Mesh class handles loading, normalizing and rendering of the fbx 3d meshes
 */
class Mesh : public QObject
{



    Q_OBJECT



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
     *@brief m_gpu will hold the gpu memory pointers for entire mesh data
     */
    MeshGPUMemory m_gpu;




    /**
     * @brief NormalizeScene will take care of the differences of scale and
     * orientation that can occur in the a fbx scene
     * @param scene is the fbx scene to be normalized
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
    void NormalizeScene(FbxScene * scene, FbxManager * fbx_manager,
                        bool convert_axis,
                        bool convert_scale,
                        bool split_points,
                        bool generate_tangents,
                        bool triangulate,
                        bool convert_textures);


    /**
     * @brief CommandLoadingBufferObjects will start the thread where GeometryLoader will work
     * @param root is the root in the fbx scene
     */
    void CommandLoadingBufferObjects(FbxNode * root);





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
     * @brief global_transform is the global transform of the mesh
     */
    QMatrix4x4 global_transform;
    /**
     *@brief should_save_scene_after_load is used to know whether the fbx file
     *has been updated and needs to be saved
     */
    bool should_save_scene_after_load;




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
     * @brief CheckLayersUsedByMesh will determine if the mesh
     * is using normals, uvs or tangents
     * @param scene is the scene on which the check is done
     */
    void CheckLayersUsedByMesh(FbxScene * scene);





    QFuture<void> geometry_loading_procces;
    QFutureWatcher<void> geometry_loading_watcher;



    /**
     *Create the lists that will be filled with mesh data
     */


    QVector<unsigned int> master_indices;
    QVector<float> master_vertices;
    QVector<float> master_normals;
    QVector<float> master_uvs;
    QVector<float> master_tangents;



private slots:
    /**
     * @brief PassGeometryDataToOpenGL will use the data harvested by GeometryLoader
     * and pass it to opengl data buffers
     */
    void PassGeometryDataToOpenGL();



signals:
   void ShouldPassGeometryDataToOpenGL();



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
     * @param file_name is the name of the file to be loaded
     * @param normalize_scene will be set to true if you want to
     * normalize axis system, scene unit and generate tangent data
     * for the loaded mesh
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
    void LoadFromFBX(FbxManager * fbx_manager,
                     QString file_name,
                     bool normalize_scene,
                     bool convert_axis = false,
                     bool convert_scale = false,
                     bool split_points = false,
                     bool generate_tangents = false,
                     bool triangulate = false,
                     bool convert_textures = false);


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
