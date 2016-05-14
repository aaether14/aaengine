#ifndef MESHENTRY_H
#define MESHENTRY_H



#include <aae_defines.hpp>




#include <QOpenGLFunctions_4_3_Core>
#include <QHash>
#include <QVector>
#include <QMatrix4x4>




#ifdef AAE_USING_FBX
#include <fbxsdk.h>
#endif




#include <fbx_manager/material/fbx_material.hpp>
#include <utils/bounding_box.hpp>
#include <utils/gl_util.hpp>




/**
 *@brief The MeshEntry class holds a mesh entry and will load its data to the
 *referenced master buffers
 */
class MeshEntry
{


    /**
     * @brief m_bbox is the bounding box of the mesh entry
     */
    aae::bounding_box3d m_bbox;


    /**
     * @brief m_local_transform holds the local transform of the mesh entry
     */
    QMatrix4x4 m_local_transform;


    /**
     *@brief m_commands is the vector containing the draw commands sorted by
     *material of the mesh entry
     */
    QHash<QString, aae::DrawElementsCommand> m_commands;




#ifdef AAE_USING_FBX
    /**
     * @brief LoadVertices will load the vertices of the mesh entry
     * @param mesh is the mesh node to be handled by this mesh entry
     * @param master_vertices - see mesh.hpp
     * @param current_control_point_offset - see mesh.hpp
     */
    void LoadVertices(FbxMesh * mesh,
                      QVector<float> & master_vertices,
                      qint32 & current_control_point_offset);


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
                     QVector<quint32> & master_indices,
                     qint32 & current_polygon_offset,
                     qint32 & current_control_point_offset);



    /**
     * @brief LoadTransform will load the transform of the mesh entry acording
     *  to its local transform and its parent's local transform
     * @param mesh is the mesh whose transform we will load
     */
    void LoadTransform(FbxMesh * mesh);


    /**
     * @brief LoadBoundingBox will load the bounding box of the mesh entry
     * @param mesh is the mesh whose bounding box we will load
     */
    void LoadBoundingBox(FbxMesh * mesh);
#endif





public:


    /**
     * @brief MeshEntry is a basic constructor
     */
    MeshEntry();
    /**
      @brief ~MeshEntry is a basic destructor
    */
    ~MeshEntry();





#ifdef AAE_USING_FBX

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



                  QVector<quint32> &master_indices,
                  QVector<float> &master_vertices,
                  QVector<float> &master_normals,
                  QVector<float> &master_uvs,
                  QVector<float> &master_tangents,


                  bool load_normals,
                  bool load_uvs,
                  bool load_tangents,



                  qint32 & current_control_point_offset,
                  qint32 & current_polygon_offset);
#endif





    /**
     * @brief GetDrawCommand get the draw command stored in the hash
     * using the provided material_name
     * @param material_name
     * @return will return the draw command
     */
    inline aae::DrawElementsCommand GetDrawCommand(const QString &material_name){
        return m_commands.value(material_name);
    }


    /**
     * @brief GetDrawCommandsm will return the draw commads of the mesh entry
     * @return
     */
    inline const QHash<QString, aae::DrawElementsCommand> &GetDrawCommands() const{
        return m_commands;
    }



    /**
     * @brief SetDrawCommands will set the draw commands of the mesh entry
     * @param commands are the draw commands that will update the mesh
     */
    inline void SetDrawCommands(const QHash<QString, aae::DrawElementsCommand> &commands){
        m_commands = commands;
    }


    /**
     * @brief DoesMaterialExist will check if there is any draw command
     * available for the provided material name
     * @param material_name will return true if the mesh entry
     *  has a component tied to this material, false otherwise
     * @return
     */
    inline bool DoesMaterialExist(const QString &material_name){
        return m_commands.contains(material_name);
    }

    /**
     * @brief GetLocalTransform will get the local transform of the mesh entry
     * @return
     */
    inline const QMatrix4x4 &GetLocalTransform() const{
        return m_local_transform;
    }


    /**
     * @brief SetLocalTransform will set the local_transform of the mesh entry
     * @param local_transform is the local transform that will update the entry
     */
    inline void SetLocalTransform(const QMatrix4x4 &local_transform){
        m_local_transform = local_transform;
    }



    /**
     * @brief GetBoundingBox will get the bounding box of the mesh entry
     * @return m_bbox;
     */
    inline const aae::bounding_box3d &GetBoundingBox() const{
        return m_bbox;
    }



    /**
     * @brief SetBoundingBox will set the bounding box of the mesh entry
     * @param bbox is the new bounding box
     */
    inline void SetBoundingBox(const aae::bounding_box3d &bbox){
        m_bbox = bbox;
    }





};






QDataStream &operator <<(QDataStream &out, const MeshEntry &entry);
QDataStream &operator >>(QDataStream &in, MeshEntry &entry);







#endif // MESHENTRY_H
