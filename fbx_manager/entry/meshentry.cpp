#include <fbx_manager/entry/meshentry.hpp>






MeshEntry::MeshEntry() : m_local_transform(QMatrix4x4())
{


    /**
    *The glorious nothing...
    */


}




MeshEntry::~MeshEntry()
{


    /**
    *Clear the commands hash
    */
    m_commands.clear();


}




#ifdef AAE_USING_FBX


void MeshEntry::LoadMesh(FbxMesh * mesh,


                         QVector<quint32> &master_indices,
                         QVector<float> &master_vertices,
                         QVector<float> &master_normals,
                         QVector<float> &master_uvs,
                         QVector<float> &master_tangents,


                         bool load_normals,
                         bool load_uvs,
                         bool load_tangents,



                         qint32 & current_control_point_offset,
                         qint32 & current_polygon_offset)
{




    /**
     *Load vertices and indices of the mesh entry
     */
    LoadIndices(mesh, master_indices, current_polygon_offset, current_control_point_offset);
    LoadVertices(mesh, master_vertices, current_control_point_offset);




    /**
    *Load the entry's layers
    */
    if (load_normals)
        LoadNormals(mesh, master_normals);


    if (load_uvs)
        LoadUVs(mesh, master_uvs);


    if (load_tangents)
        LoadTangents(mesh, master_tangents);



    /**
     *Compute the transform and bounding box and load them
     */
    LoadTransform(mesh);
    LoadBoundingBox(mesh);



}







void MeshEntry::LoadVertices(FbxMesh * mesh,
                             QVector<float> &master_vertices,
                             qint32 &current_control_point_offset)
{



    for (qint32 i = 0; i < mesh->GetControlPointsCount(); i++)
    {


        master_vertices << (float)(mesh->GetControlPointAt(i).mData[0]);
        master_vertices << (float)(mesh->GetControlPointAt(i).mData[1]);
        master_vertices << (float)(mesh->GetControlPointAt(i).mData[2]);


    }


    /**
    *Advance current position in the vertex buffers
    */
    current_control_point_offset += mesh->GetControlPointsCount();



}











void MeshEntry::LoadIndices(FbxMesh *mesh,
                            QVector<quint32> &master_indices,
                            qint32 &current_polygon_offset,
                            qint32 &current_control_point_offset)
{




    /**
     *We need to map indices per material
     */
    QHash<qint32, QVector<quint32> > material_mapped_indices;
    FbxLayerElementArrayTemplate<qint32> *material_indices;



    /**
    *Extract information from fbx mesh
    */
    mesh->GetMaterialIndices(&material_indices);




    for (qint32 i = 0; i < mesh->GetPolygonCount(); i++)
    {
        material_mapped_indices[material_indices->GetAt(i)] << (quint32)(mesh->GetPolygonVertex(i, 0));
        material_mapped_indices[material_indices->GetAt(i)] << (quint32)(mesh->GetPolygonVertex(i, 1));
        material_mapped_indices[material_indices->GetAt(i)] << (quint32)(mesh->GetPolygonVertex(i, 2));
    }



    /**
    *Create draw commands
    */
    foreach(auto it, material_mapped_indices.keys())
    {


        master_indices << material_mapped_indices[it];


        DrawElementsCommand c;
        c.baseInstance = 0;
        c.instanceCount = 1;
        c.baseVertex = current_control_point_offset;
        c.firstIndex = current_polygon_offset;
        c.vertexCount = material_mapped_indices[it].size();
        m_commands.insert(QString(mesh->GetNode()->GetMaterial(it)->GetName()), c);
        current_polygon_offset += c.vertexCount;


    }



}



void MeshEntry::LoadTransform(FbxMesh *mesh)
{





    FbxVector4 T = mesh->GetNode()->GetGeometricTranslation (FbxNode::eSourcePivot);
    FbxVector4 R = mesh->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 S = mesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
    FbxAMatrix geometric_offset_transform(T, R, S);





    FbxAMatrix transform = mesh->GetNode()->GetScene()->GetAnimationEvaluator()->GetNodeGlobalTransform(mesh->GetNode()) *
            geometric_offset_transform;





    for (qint32 i = 0; i < 4; i++)
        for (qint32 j = 0; j < 4; j++)
            m_local_transform(i, j) = transform.Transpose().Get(i, j);




}




void MeshEntry::LoadBoundingBox(FbxMesh *mesh)
{



    /**
    *First compute the bounding box
    */
    mesh->ComputeBBox();


    /**
     *Then extract the data
     */
    QVector3D BBMin = QVector3D(mesh->BBoxMin.Get().mData[0], mesh->BBoxMin.Get().mData[1], mesh->BBoxMin.Get().mData[2]);
    QVector3D BBMax = QVector3D(mesh->BBoxMax.Get().mData[0], mesh->BBoxMax.Get().mData[1], mesh->BBoxMax.Get().mData[2]);


    /**
   *Create the entry's bounding box
   */
    m_bbox = aae::bounding_box3d(BBMin, BBMax);



}
#endif








QDataStream &operator <<(QDataStream &out, const MeshEntry &entry)
{

    /**
    *Output to datastream all entry's information
    */
    out << entry.GetLocalTransform() << entry.GetDrawCommands() << entry.GetBoundingBox();
    return out;

}



QDataStream &operator >>(QDataStream &in, MeshEntry &entry)
{


    /**
     *Extract from datastream all entry's information
     */
    QMatrix4x4 local_transform;
    QHash<QString, DrawElementsCommand> commands;
    aae::bounding_box3d bbox;



    in >> local_transform >> commands >> bbox;


    entry.SetLocalTransform(local_transform);
    entry.SetDrawCommands(commands);
    entry.SetBoundingBox(bbox);
    return in;

}










