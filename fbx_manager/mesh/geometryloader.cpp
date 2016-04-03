#include <fbx_manager/mesh/geometryloader.hpp>





void GeometryLoader::CheckLayersUsedByMesh()
{




    /**
    *Loop through the meshes and see if the have normals, uvs, or tangents
    */


    for (int i = 0; i < m_scene->GetGeometryCount(); i++)
    {



        FbxMesh * current_mesh = FbxCast<FbxMesh>(m_scene->GetGeometry(i));



        if (!current_mesh)
            continue;



        if (current_mesh->GetElementNormalCount() > 0)
            is_using_normals = true;



        if (current_mesh->GetElementUVCount() > 0)
            is_using_uvs = true;




        if (current_mesh->GetElementTangentCount() > 0)
            is_using_tangents = true;




    }



    /**
    *If the mesh has uvs but no textures then we will not load the uv data
    */

    if (is_using_uvs && !m_scene->GetTextureCount() > 0)
        is_using_uvs = false;



    /**
    *If not even the tangent information is present on the mesh then exit
    */


    if (!is_using_tangents)
        return;



    is_using_tangents = false;


    /**
     *Otherwise, see if there are any bump maps inside the mesh
    */

    for (int i = 0; i < m_scene->GetMaterialCount(); i++)
    {



        if (!m_scene->GetMaterial(i))
            continue;



        FbxProperty normal_map_property = m_scene->GetMaterial(i)->FindProperty(FbxSurfaceMaterial::sNormalMap);



        if (normal_map_property.GetSrcObjectCount<FbxFileTexture>() > 0)
        {
            is_using_tangents = true;
            break;
        }




    }




}







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
                               bool &using_normals,
                               bool &using_uvs,
                               bool &using_tangents,
                               FbxScene *scene) :
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
    m_scene(scene)
{


    /**
    *This will fill the reference table for the geometry loader
    */


}



void GeometryLoader::Load()
{



    if (m_scene)
    {
        CheckLayersUsedByMesh();
        RecursiveLoad(m_scene->GetRootNode());
    }



    emit HasFinishedLoading();


}
