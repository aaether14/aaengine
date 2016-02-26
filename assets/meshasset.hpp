#ifndef MESHASSET_H
#define MESHASSET_H



#include <assets/baseasset.hpp>
#include <fbx_manager/mesh.hpp>




class MeshAsset : public BaseAsset
{


    Mesh * mesh;



public:
    MeshAsset();
    ~MeshAsset();



    bool isLoaded();


    Mesh *GetMesh();



};

#endif // MESHASSET_H
