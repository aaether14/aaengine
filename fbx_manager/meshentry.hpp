#ifndef MESHENTRY_H
#define MESHENTRY_H





#include <QOpenGLFunctions_4_3_Core>
#include <QMap>
#include <QVector>
#include <QMatrix4x4>
#include <fbxsdk.h>
#include <fbx_manager/material.hpp>





class MeshEntry
{




    QMatrix4x4 local_transform;
    QMap<QString, DrawElementsCommand> commands;




    void MapMaterialsToTheirNames(FbxMesh * mesh);



    void LoadVertices(FbxMesh * mesh,
                      QVector<float> & master_vertices,
                      int & current_control_point_offset);


    void LoadNormals(FbxMesh * mesh,
                     QVector<float> & master_normals);


    void LoadUVs(FbxMesh *mesh, QVector<float> & master_uvs);



    void LoadIndices(FbxMesh * mesh,
                     QVector<unsigned int> & master_indices,
                     int & current_polygon_offset,
                     int & current_control_point_offset);


    void LoadTransform(FbxMesh * mesh);



public:


    MeshEntry();
    ~MeshEntry();



    void LoadMesh(FbxMesh * mesh,
                  QVector<unsigned int> &master_indices,
                  QVector<float> &master_vertices,
                  QVector<float> &master_normals,
                  QVector<float> &master_uvs,
                  int & current_control_point_offset,
                  int & current_polygon_offset);





    inline DrawElementsCommand GetDrawCommand(QString material_name){return commands[material_name]; }
    inline bool DoesMaterialExist(QString material_name){return commands.count(material_name) > 0;}


    inline QMatrix4x4 GetLocalTransform(){return local_transform; }





};

#endif // MESHENTRY_H
