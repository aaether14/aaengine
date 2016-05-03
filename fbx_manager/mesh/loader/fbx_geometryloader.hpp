#ifndef GEOMETRYLOADER_H
#define GEOMETRYLOADER_H



#include <aae_defines.hpp>
#ifdef AAE_USING_FBX



#include <fbx_manager/entry/meshentry.hpp>




/**
 *@brief The GeometryLoader class has the purpose of loading the geometry data
 *of a 3d model
 */
class GeometryLoader
{



    /**
     *@brief m_mesh_entries is the list of mesh entries the loader will attempt
     *to load
     */
    QList<MeshEntry> &m_mesh_entries;


    /**
     * @brief d_master_indices - see mesh.hpp
     */
    QVector<quint32> & d_master_indices;
    /**
     * @brief d_master_vertices - see mesh.hpp
     */
    QVector<float> & d_master_vertices;
    /**
     * @brief d_master_normals - see mesh.hpp
     */
    QVector<float> & d_master_normals;
    /**
     * @brief d_master_uvs - see mesh.hpp
     */
    QVector<float> & d_master_uvs;
    /**
     * @brief d_master_tangents - see mesh.hpp
     */
    QVector<float> & d_master_tangents;



    /**
     *@brief current_polygon_offset is used to know how to fill the mesh entry
     *draw command
     */
    qint32 current_polygon_offset;
    /**
     *@brief current_control_point_offset is used to know how to fill the mesh
     *entry draw command
     */
    qint32 current_control_point_offset;



    /**
     *@brief is_using_normals will be true if the mesh is using normals for
     *rendering
     */
    bool & is_using_normals;
    /**
     *@brief is_using_uvs will be true if the mesh is using uvs for rendering
     *(i.e has diffuse textures)
     */
    bool & is_using_uvs;
    /**
     *@brief is_using_tangents will be true if the mesh using tangents for
     *rendering (i.e has bump maps)
     */
    bool & is_using_tangents;



    /**
     * @brief scene is the scene pointer of the mesh to be loaded
     */
    FbxScene * m_scene;



    /**
     * @brief RecursiveLoad will recursively look through all the nodes in the scene and load data acordingly
     * @param node is the current node we're looking into
     */
    void RecursiveLoad(FbxNode * node);



    /**
     * @brief CheckLayersUsedByMesh will determine if the mesh
     * is using normals, uvs or tangents
     */
    void CheckLayersUsedByMesh();



public:


    /**
     * @brief GeometryLoader is a basic contructor
     * @param entries is a reference to the list
     *  of mesh entries we attempt to fill
     */
    GeometryLoader(QList<MeshEntry> & r_entries,
                   QVector<quint32> & r_indices,
                   QVector<float> & r_vertices,
                   QVector<float> & r_normals,
                   QVector<float> & r_uvs,
                   QVector<float> & r_tangents,
                   bool & using_normals,
                   bool & using_uvs,
                   bool & using_tangents,
                   FbxScene * r_scene);




    /**
     *@brief Load - this slot will be connected to thread start
     */
    void Load();


};
#endif



#endif // GEOMETRYLOADER_H
