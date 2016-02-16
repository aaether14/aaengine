#ifndef MESH_H
#define MESH_H





#include <QDebug>
#include <QOpenGLTexture>
#include <QImage>
#include <QFileInfo>




#include <QOpenGLContext>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>




#include <fbx_manager/fbxmanager.hpp>
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



    GLuint ssbo;
    GLuint indirect_buffer;
    GLuint per_object_buffer;




    QString ComputeTextureFilename(QString texture_name, QString fbx_file_name);



    void NormalizeScene(FbxScene * scene, FbxManager * fbx_manager);



    void LoadBufferObjects(FbxNode * root, QOpenGLShaderProgram & shader);




    void RecursiveLoad(FbxNode * node,
                       QOpenGLShaderProgram &shader,
                       QVector<unsigned int> & master_indices,
                       QVector<float> & master_vertices,
                       QVector<float> & master_normals,
                       QVector<float> & master_uvs);




    void LoadMaterials(FbxScene * scene, QOpenGLShaderProgram & shader, QString fbx_file_name);





    void CacheDrawCommands(QVector<MeshEntry *> &mesh_entries,
                           QVector<DrawElementsCommand> & draw_commands,
                           QVector<unsigned int> &per_object_index,
                           QString key);





    QMatrix4x4 global_transform;
    bool should_save_scene_after_load;




    QOpenGLVertexArrayObject master_vao;
    QOpenGLBuffer master_ibo;
    QOpenGLBuffer master_vbo;
    QOpenGLBuffer master_normals_vbo;
    QOpenGLBuffer master_uvs_vbo;




    int current_polygon_offset;
    int current_control_point_offset;




    bool is_loaded;





public:




    Mesh();
    ~Mesh();



    void LoadFromFBX(FBXManager * fbx_manager, QOpenGLShaderProgram & shader, const char * file_name);



    inline void SetGlobalTransform(QMatrix4x4 transform) {global_transform = transform; }
    void Draw(QOpenGLShaderProgram & shader);





};



#endif // MESH_H
