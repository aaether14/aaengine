#include <assets/meshasset.hpp>



MeshAsset::MeshAsset() :
    m_mesh(NULL)
{

    m_mesh = new Mesh();

}



MeshAsset::~MeshAsset()
{

    delete m_mesh;


}




bool MeshAsset::hasData()
{


    return m_mesh != NULL;


}



bool MeshAsset::isLoaded()
{


    return m_mesh->IsLoaded();


}



Mesh *MeshAsset::GetMesh()
{


    return m_mesh;


}
