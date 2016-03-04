#ifndef MESHASSET_H
#define MESHASSET_H



#include <assets/baseasset.hpp>
#include <fbx_manager/mesh.hpp>




/**
 *@brief The MeshAsset class derives from BaseAsset and will provide isLoaded()
 *definition
 */
class MeshAsset : public BaseAsset
{


    /**
     *@brief mesh is the fbx mesh encapsulated inside the asset
     */
    Mesh * mesh;



public:

    /**
     * @brief MeshAsset will allocate memory for the Mesh
     */
    MeshAsset();
    /**
      @brief ~MeshAsset will delete the Mesh from memory
    */
    ~MeshAsset();


    /**
     * @brief isLoaded will return true if the Mesh has been successfully created
     * @return
     */
    bool isLoaded();

    /**
     * @brief GetMesh will return the encapsulated mesh
     * @return
     */
    Mesh *GetMesh();



};

#endif // MESHASSET_H
