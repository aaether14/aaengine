#include <assets/meshasset.hpp>



MeshAsset::MeshAsset()
{

    mesh = new Mesh();

}



MeshAsset::~MeshAsset()
{

    delete mesh;


}




bool MeshAsset::isLoaded()
{


    return mesh != 0;


}



Mesh *MeshAsset::GetMesh()
{


    return mesh;


}
