#ifndef MESHENTRY_H
#define MESHENTRY_H





#include <QOpenGLFunctions_4_3_Core>
#include <QHash>
#include <QVector>
#include <QMatrix4x4>
#include <fbxsdk.h>
#include <fbx_manager/material/material.hpp>





/**
 *@brief The MeshEntry class holds a mesh entry and will load its data to the
 *referenced master buffers
 */
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


    /**
     * @brief LoadNormals will load the normals of the mesh entry
     * @param mesh is the mesh node to be handled by this mesh entry
     * @param master_normals - see mesh.hpp
     */
    void LoadNormals(FbxMesh * mesh,
                     QVector<float> & master_normals);


    /**
     * @brief LoadUVs will load the uvs of the mesh entry
     * @param mesh is the mesh node to be handled by this mesh entry
     * @param master_uvs - see mesh.hpp
     */
    void LoadUVs(FbxMesh *mesh,
                 QVector<float> & master_uvs);




    /**
     * @brief LoadTangents will load the tangents of the mesh entry
     * @param mesh is the mesh not to be handled by this mesh entry
     * @param master_tangents - see mesh.hpp
     */
    void LoadTangents(FbxMesh * mesh,
                      QVector<float> &master_tangents);



    /**
     * @brief LoadIndices will load the indices of the mesh entry
     * @param mesh is the mesh node the be handled by this mesh entry
     * @param master_indices - see mesh.hpp
     * @param current_polygon_offset - see mesh.hpp
     * @param current_control_point_offset - see mesh.hpp
     */
    void LoadIndices(FbxMesh * mesh,
                     QVector<unsigned int> & master_indices,
                     int & current_polygon_offset,
                     int & current_control_point_offset);



    /**
     * @brief LoadTransform will load the transform of the mesh entry acording
     *  to its local transform and its parent's local transform
     * @param mesh is the mesh whose transform we will load
     */
    void LoadTransform(FbxMesh * mesh);



public:


    /**
     * @brief MeshEntry - basic constructor
     */
    MeshEntry();
    /**
      @brief ~MeshEntry - basic destructor
    */
    ~MeshEntry();


    /**
     * @brief LoadMesh will load the provided mesh to the master buffers
     * @param mesh the mesh to be loaded
     * @param master_indices - see mesh.hpp
     * @param master_vertices - see mesh.hpp
     * @param master_normals - see mesh.hpp
     * @param master_uvs - see mesh.hpp
     * @param master_tangents - see mesh.hpp
     * @param load_normals is true if the mesh has normals
     * to load
     * @param load_uvs is true if the mesh has uvs to load
     * @param load_tangents is true if the mesh has tangents
     * to load
     * @param current_control_point_offset - see mesh.hpp
     * @param current_polygon_offset - see mesh.hpp
     */
    void LoadMesh(FbxMesh * mesh,



                  QVector<unsigned int> &master_indices,
                  QVector<float> &master_vertices,
                  QVector<float> &master_normals,
                  QVector<float> &master_uvs,
                  QVector<float> &master_tangents,


                  bool load_normals,
                  bool load_uvs,
                  bool load_tangents,



                  int & current_control_point_offset,
                  int & current_polygon_offset);




    /**
     * @brief GetDrawCommand get the draw command stored in the hash
     * using the provided material_name
     * @param material_name
     * @return will return the draw command
     */
    inline DrawElementsCommand GetDrawCommand(QString material_name){return commands.value(material_name); }
    /**
     * @brief DoesMaterialExist will check if there is any draw command
     * available for the provided material name
     * @param material_name will return true if the mesh entry
     *  has a component tied to this material, false otherwise
     * @return
     */
    inline bool DoesMaterialExist(QString material_name){return commands.contains(material_name); }

    /**
     * @brief GetLocalTransform will get the local transform of the mesh entry
     * @return
     */
    inline QMatrix4x4 GetLocalTransform(){return local_transform; }





};

#endif // MESHENTRY_H
