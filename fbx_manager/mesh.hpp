#ifndef MESH_H
#define MESH_H





#include <QDebug>
#include <QSharedPointer>
#include <fbx_manager/fbxmanager.hpp>
#include <fbx_manager/meshentry.hpp>





class Mesh
{


    QVector<QSharedPointer<MeshEntry> > mesh_entries;
    void RecursiveLoad(FbxNode * node, QOpenGLShaderProgram &shader);


    QMap<QString, QOpenGLTexture*> texture_cache;
    bool should_save_scene_after_load;
    QString directory;



public:



    Mesh();
    ~Mesh();



    void LoadFromFBX(FBXManager * fbx_manager, QOpenGLShaderProgram & shader, const char * file_name);
    void Draw(QOpenGLFunctions * f);




};



#endif // MESH_H
