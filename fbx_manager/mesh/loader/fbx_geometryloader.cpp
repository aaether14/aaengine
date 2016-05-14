#include <fbx_manager/mesh/loader/fbx_geometryloader.hpp>




#ifdef AAE_USING_FBX
void GeometryLoader::CheckLayersUsedByMesh()
{




    /**
    *Loop through the meshes and see if the have normals, uvs, or tangents
    */
    for (qint32 i = 0; i < m_scene->GetGeometryCount(); i++)
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
    for (qint32 i = 0; i < m_scene->GetMaterialCount(); i++)
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




    for (qint32 i = 0; i < node->GetChildCount(); i++)
        RecursiveLoad(node->GetChild(i));





    if(!node->GetNodeAttribute())
        return;





    FbxNodeAttribute::EType AttributeType = node->GetNodeAttribute()->GetAttributeType();
    if(AttributeType != FbxNodeAttribute::eMesh)
        return;




    FbxMesh * mesh = node->GetMesh();




    MeshEntry new_mesh_entry;
    new_mesh_entry.LoadMesh(mesh,


                             d_master_indices,
                             d_master_vertices,
                             d_master_normals,
                             d_master_uvs,
                             d_master_tangents,


                             is_using_normals,
                             is_using_uvs,
                             is_using_tangents,


                             current_control_point_offset,
                             current_polygon_offset);





    m_mesh_entries << new_mesh_entry;




}




GeometryLoader::GeometryLoader(QList<MeshEntry> &r_entries,
                               QVector<quint32> &r_indices,
                               QVector<float> &r_vertices,
                               QVector<float> &r_normals,
                               QVector<float> &r_uvs,
                               QVector<float> &r_tangents,
                               bool &using_normals,
                               bool &using_uvs,
                               bool &using_tangents,
                               FbxScene *r_scene) :
    m_mesh_entries(r_entries),
    d_master_indices(r_indices),
    d_master_vertices(r_vertices),
    d_master_normals(r_normals),
    d_master_uvs(r_uvs),
    d_master_tangents(r_tangents),
    current_polygon_offset(0),
    current_control_point_offset(0),
    is_using_normals(using_normals),
    is_using_uvs(using_uvs),
    is_using_tangents(using_tangents),
    m_scene(r_scene)
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



}
#endif

