#include <assets/meshasset.hpp>



MeshAsset::MeshAsset() :
    m_mesh(NULL)
{

    /**
    *Allocate memory for the mesh
    */
    m_mesh = new Mesh();

}



MeshAsset::~MeshAsset()
{

    /**
    *Delete the mesh
    */
    delete m_mesh;


}




bool MeshAsset::hasData()
{


    /**
    *Check if the mesh allocated memory
    */
    return m_mesh != NULL;


}



bool MeshAsset::isLoaded()
{


    /**
    *Check if the mesh has loaded correctly
    */
    return m_mesh->IsLoaded();


}



Mesh *MeshAsset::GetMesh()
{

    /**
    *Get a refernce to the mesh
    */
    return m_mesh;


}
