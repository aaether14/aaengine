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
#include <fbxsdk.h>





class MeshEntry
{



    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer ibo;
    QOpenGLBuffer vertices_vbo;
    QOpenGLBuffer normals_vbo;
    QOpenGLBuffer uvs_vbo;



    QMap<QString, QString> textures;
    int tri_count;



    void LoadVertices(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void LoadNormals(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void LoadMaterials(FbxMesh * mesh, QOpenGLShaderProgram & shader, QString directory, QMap<QString, QOpenGLTexture *> &texture_cache);
    void LoadUVs(FbxMesh *mesh, QOpenGLShaderProgram &shader);
    void LoadIndices(FbxMesh * mesh);



    QString ComputeTextureFilename(QString file_name, QString directory);



public:


    MeshEntry();
    ~MeshEntry();



    void LoadMesh(FbxMesh * mesh, QOpenGLShaderProgram & shader, QString directory, QMap<QString, QOpenGLTexture *> &texture_cache);
    void Draw(QOpenGLFunctions * f, QMap<QString, QOpenGLTexture *> &texture_cache);



};

#endif // MESHENTRY_H
