#ifndef MESH_H
#define MESH_H





#include <QDebug>
#include <QOpenGLTexture>
#include <QImage>
#include <QFileInfo>




#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>




#include <fbx_manager/meshentry.hpp>





class Mesh
{



    typedef struct float16 { float m[16]; } float16;
    float16 toFloat16(const float* arr){float16 v; memcpy(&v, arr, sizeof(float16)); return v;}




    QVector<MeshEntry*> mesh_entries;
    QHash<QString, QOpenGLTexture*> textures;
    QHash<QString, Material> materials;
    QHash<QString, QVector<DrawElementsCommand> > commands_cache;
    QHash<QString, QVector<unsigned int> > per_object_index_cache;



    GLuint vao;


    GLuint ssbo;
    GLuint indirect_buffer;
    GLuint per_object_buffer;



    GLuint master_vbo;
    GLuint master_ibo;
    GLuint master_normals_vbo;
    GLuint master_uvs_vbo;




    QString ComputeTextureFilename(QString texture_name, QString fbx_file_name);



    void NormalizeScene(FbxScene * scene, FbxManager * fbx_manager);



    void LoadBufferObjects(FbxNode * root);




    void RecursiveLoad(FbxNode * node,
                       QVector<unsigned int> & master_indices,
                       QVector<float> & master_vertices,
                       QVector<float> & master_normals,
                       QVector<float> & master_uvs);




    void LoadMaterials(FbxScene * scene, QString fbx_file_name);





    void CacheDrawCommands(QVector<MeshEntry *> &mesh_entries,
                           QVector<DrawElementsCommand> & draw_commands,
                           QVector<unsigned int> &per_object_index,
                           QString key);





    QMatrix4x4 global_transform;
    bool should_save_scene_after_load;




    int current_polygon_offset;
    int current_control_point_offset;




    bool is_loaded;
    int draw_method;




    enum
    {
        DYANIMC_DRAW,
        CACHED_DRAW
    };






    void DynamicDraw(QOpenGLShaderProgram & shader,
                     QOpenGLFunctions_4_3_Core * f,
                     QString material_name);




    void CachedDraw(QOpenGLShaderProgram & shader,
                    QOpenGLFunctions_4_3_Core * f,
                    QString material_name);





public:




    Mesh();
    ~Mesh();



    void LoadFromFBX(FbxManager * fbx_manager, QString file_name);




    inline void SetGlobalTransform(QMatrix4x4 transform) {global_transform = transform; }
    inline void SetDrawMethod(int method){draw_method = method; }




    void Draw(QOpenGLShaderProgram & shader);





};



#endif // MESH_H
