#ifndef MESHENTRY_H
#define MESHENTRY_H




#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QImage>
#include <QVector>
#include <fbxsdk.h>





class MeshEntry
{



    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer ibo;
    QOpenGLBuffer vertices_vbo;
    QOpenGLBuffer normals_vbo;
    QOpenGLBuffer uvs_vbo;
    QOpenGLTexture *material_texture;


    int tri_count;



    void LoadVertices(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void LoadNormals(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void LoadMaterials(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void LoadUVs(FbxMesh *mesh, QOpenGLShaderProgram &shader);
    void LoadIndices(FbxMesh * mesh);



public:


    MeshEntry();
    ~MeshEntry();



    void LoadMesh(FbxMesh * mesh, QOpenGLShaderProgram & shader);
    void Draw(QOpenGLFunctions * f);



};

#endif // MESHENTRY_H