#ifndef MESHENTRY_H
#define MESHENTRY_H





#include <QOpenGLFunctions_4_3_Core>
#include <QVector>
#include <QMatrix4x4>
#include <fbxsdk.h>





class MeshEntry
{




    QMatrix4x4 local_transform;
    GLuint count;
    GLuint index;
    GLuint base_vertex;



    void LoadVertices(FbxMesh * mesh,
                      QVector<float> & master_vertices,
                      int & current_control_point_offset);


    void LoadNormals(FbxMesh * mesh,
                     QVector<float> & master_normals);


    void LoadMaterials(FbxMesh * mesh);



    void LoadUVs(FbxMesh *mesh);


    void LoadIndices(FbxMesh * mesh,
                     QVector<unsigned int> & master_indices,
                     int & current_polygon_offset,
                     int & current_control_point_offset);


    void LoadTransform(FbxMesh * mesh);




    void LoadDiffuseMaterial(FbxSurfaceMaterial * material);



public:


    MeshEntry();
    ~MeshEntry();



    void LoadMesh(FbxMesh * mesh,
                  QVector<unsigned int> &master_indices,
                  QVector<float> &master_vertices,
                  QVector<float> &master_normals,
                  int & current_control_point_offset,
                  int & current_polygon_offset);




    inline GLuint GetCount(){return count; }
    inline GLuint GetIndex(){return index; }
    inline GLuint GetBaseVertex(){return base_vertex; }
    inline QMatrix4x4 GetLocalTransform(){return local_transform; }





};

#endif // MESHENTRY_H
