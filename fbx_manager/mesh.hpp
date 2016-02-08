#ifndef MESH_H
#define MESH_H





#include <QDebug>
#include <QSharedPointer>
#include <fbx_manager/fbxmanager.hpp>
#include <fbx_manager/meshentry.hpp>





class Mesh
{


    QVector<QSharedPointer<MeshEntry> > mesh_entries;
    void RecursiveLoad(FbxNode * node, QOpenGLShaderProgram &shader, QString fbx_file_name);
    void LoadTextures(FbxScene * scene);


    QMatrix4x4 global_transform;
    QOpenGLTexture *texture_array;
    QMap<QString, int> texture_map;
    bool should_save_scene_after_load;



public:



    Mesh();
    ~Mesh();



    void LoadFromFBX(FBXManager * fbx_manager, QOpenGLShaderProgram & shader, const char * file_name);
    void Draw(QOpenGLFunctions * f, QOpenGLShaderProgram & shader);
    inline void SetGlobalTransform(QMatrix4x4 transform) {global_transform = transform; }




};



#endif // MESH_H
