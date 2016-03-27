#include <fbx_manager/mesh/geometryloader.hpp>




void GeometryLoader::RecursiveLoad(FbxNode *node)
{




    for (int i = 0; i < node->GetChildCount(); i++)
        RecursiveLoad(node->GetChild(i));





    if(!node->GetNodeAttribute())
        return;





    FbxNodeAttribute::EType AttributeType = node->GetNodeAttribute()->GetAttributeType();
    if(AttributeType != FbxNodeAttribute::eMesh)
        return;




    FbxMesh * mesh = node->GetMesh();




    MeshEntry * new_mesh_entry = new MeshEntry();
    new_mesh_entry->LoadMesh(mesh,


                             master_indices,
                             master_vertices,
                             master_normals,
                             master_uvs,
                             master_tangents,


                             is_using_normals,
                             is_using_uvs,
                             is_using_tangents,


                             current_control_point_offset,
                             current_polygon_offset);





    mesh_entries << new_mesh_entry;




}



GeometryLoader::GeometryLoader(QList<MeshEntry *> &entries,
                               QVector<unsigned int> &indices,
                               QVector<float> &vertices,
                               QVector<float> &normals,
                               QVector<float> &uvs,
                               QVector<float> &tangents,
                               bool using_normals,
                               bool using_uvs,
                               bool using_tangents,
                               FbxNode *root) :
    mesh_entries(entries),
    master_indices(indices),
    master_vertices(vertices),
    master_normals(normals),
    master_uvs(uvs),
    master_tangents(tangents),
    current_polygon_offset(0),
    current_control_point_offset(0),
    is_using_normals(using_normals),
    is_using_uvs(using_uvs),
    is_using_tangents(using_tangents),
    root_node(root)
{


    /**
    *This will fill the reference table for the geometry loader
    */


}



void GeometryLoader::Load()
{



    if (root_node)
        RecursiveLoad(root_node);



    emit HasFinishedLoading();


}
