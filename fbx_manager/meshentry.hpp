#ifndef MESHENTRY_H
#define MESHENTRY_H





#include <QOpenGLFunctions_4_3_Core>
#include <QHash>
#include <QVector>
#include <QMatrix4x4>
#include <fbxsdk.h>
#include <fbx_manager/material.hpp>





class MeshEntry
{



    /**
     * @brief local_transform holds the local transform of the mesh entry
     */
    QMatrix4x4 local_transform;


    /**
     *@brief commands is the vector containing the draw commands sorted by
     *material of the mesh entry
     */
    QHash<QString, DrawElementsCommand> commands;



    /**
     * @brief LoadVertices will load the vertices of the mesh entry
     * @param mesh is the mesh node to be handled by this mesh entry
     * @param master_vertices - see mesh.hpp
     * @param current_control_point_offset - see mesh.hpp
     */
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





    inline DrawElementsCommand GetDrawCommand(QString material_name){return commands.value(material_name); }
    inline bool DoesMaterialExist(QString material_name){return commands.contains(material_name); }


    inline QMatrix4x4 GetLocalTransform(){return local_transform; }





};

#endif // MESHENTRY_H
