#ifndef MESHENTRY_H
#define MESHENTRY_H





#include <QVector>
#include <QMatrix4x4>
#include <fbxsdk.h>





class MeshEntry
{




    QMatrix4x4 local_transform;



    void LoadVertices(FbxMesh * mesh,
                      QVector<float> & master_vertices,
                      int & current_control_point_offset);


    void LoadNormals(FbxMesh * mesh);


    void LoadMaterials(FbxMesh * mesh);



    void LoadUVs(FbxMesh *mesh);


    void LoadIndices(FbxMesh * mesh,
                     QVector<unsigned int> & master_indices,
                     int & current_polygon_offset);


    void LoadTransform(FbxMesh * mesh);




    void LoadDiffuseMaterial(FbxSurfaceMaterial * material);



public:


    MeshEntry();
    ~MeshEntry();



    void LoadMesh(FbxMesh * mesh,
                  QVector<unsigned int> &master_indices,
                  QVector<float> &master_vertices,
                  int & current_control_point_offset,
                  int & current_polygon_offset);




};

#endif // MESHENTRY_H
