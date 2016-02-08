#ifndef MESHENTRY_H
#define MESHENTRY_H




#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QImage>
#include <QFileInfo>
#include <QMap>
#include <QVector>
#include <QMatrix4x4>
#include <fbxsdk.h>





class MeshEntry
{



    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer ibo;
    QOpenGLBuffer vertices_vbo;
    QOpenGLBuffer normals_vbo;
    QOpenGLBuffer uvs_vbo;
    QOpenGLBuffer material_indices_vbo;



    QMap<QString, QString> textures;
    QMap<QString, QVector3D> colors;



    QMatrix4x4 local_transform;
    QMatrix4x4 * global_transform_ptr;
    int tri_count;



    void LoadVertices(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void LoadNormals(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void LoadMaterials(FbxMesh * mesh, QOpenGLShaderProgram & shader, QString fbx_file_name,
                       QMap<QString, QOpenGLTexture *> &texture_cache);
    void LoadMaterialIndices(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void LoadUVs(FbxMesh *mesh, QOpenGLShaderProgram &shader);
    void LoadIndices(FbxMesh * mesh);
    void LoadTransform(FbxMesh * mesh);



    QString ComputeTextureFilename(QString texture_name, QString fbx_file_name);
    void LoadDiffuseMaterial(FbxSurfaceMaterial * material,
                             QOpenGLShaderProgram & shader, QString fbx_file_name,
                             QMap<QString, QOpenGLTexture *> &texture_cache);



public:


    MeshEntry();
    ~MeshEntry();



    void LoadMesh(FbxMesh * mesh, QOpenGLShaderProgram & shader,
                  QString fbx_file_name, QMatrix4x4 *global_transform,
                  QMap<QString, QOpenGLTexture *> &texture_cache);
    void Draw(QOpenGLFunctions * f, QMap<QString, QOpenGLTexture *> &texture_cache, QOpenGLShaderProgram & shader);



};

#endif // MESHENTRY_H
