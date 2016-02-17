#include <fbx_manager/meshentry.hpp>






MeshEntry::MeshEntry()
{



}






MeshEntry::~MeshEntry()
{



}




void MeshEntry::LoadMesh(FbxMesh * mesh,
                         QVector<unsigned int> &master_indices,
                         QVector<float> &master_vertices,
                         QVector<float> &master_normals, QVector<float> &master_uvs,
                         int & current_control_point_offset,
                         int & current_polygon_offset)
{




    LoadIndices(mesh, master_indices, current_polygon_offset, current_control_point_offset);
    LoadVertices(mesh, master_vertices, current_control_point_offset);
    LoadNormals(mesh, master_normals);
    LoadUVs(mesh, master_uvs);
    LoadTransform(mesh);




}







void MeshEntry::LoadVertices(FbxMesh * mesh,
                             QVector<float> &master_vertices,
                             int & current_control_point_offset)
{



    for (int i = 0; i < mesh->GetControlPointsCount(); i++)
    {
        master_vertices << (float)(mesh->GetControlPointAt(i).mData[0]);
        master_vertices << (float)(mesh->GetControlPointAt(i).mData[1]);
        master_vertices << (float)(mesh->GetControlPointAt(i).mData[2]);
    }



    current_control_point_offset += mesh->GetControlPointsCount();



}




void MeshEntry::LoadNormals(FbxMesh * mesh,
                            QVector<float> &master_normals)
{



    if(mesh->GetElementNormalCount() < 1)
    {

        for (int i = 0; i < mesh->GetControlPointsCount(); i++)
            master_normals << 0.0 << 0.0 << 0.0;


        qDebug() << "Invalid normals!";
        return;

    }




    FbxGeometryElementNormal* vertex_normal = mesh->GetElementNormal(0);
    if (vertex_normal->GetMappingMode() == FbxGeometryElement::eByControlPoint)
    {


    }
    else
    {
        qDebug() << "Invalid normal format!";
    }




    for (int i = 0; i < mesh->GetControlPointsCount(); i++)
    {


        master_normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[0]);
        master_normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[1]);
        master_normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[2]);


    }



}











void MeshEntry::LoadUVs(FbxMesh *mesh, QVector<float> &master_uvs)
{


    if (mesh->GetElementUVCount() < 1)
    {

        for (int i = 0; i < mesh->GetControlPointsCount(); i++)
            master_uvs << 0.0 << 0.0;


        qDebug() << "Invalid UVs!";
        return;

    }



    FbxGeometryElementUV* vertex_uv = mesh->GetElementUV(0);
    if (vertex_uv->GetMappingMode() == FbxGeometryElement::eByControlPoint)
    {


    }
    else
    {
        qDebug() << "Invalid UV format!";
    }



    QVector<float> uvs;
    for (int i = 0; i < mesh->GetControlPointsCount(); i++)
    {


        master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[0]);
        master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[1]);


    }




}






void MeshEntry::LoadIndices(FbxMesh *mesh,
                            QVector<unsigned int> &master_indices,
                            int &current_polygon_offset,
                            int &current_control_point_offset)
{





    QHash<int, QVector<unsigned int> > material_mapped_indices;
    FbxLayerElementArrayTemplate<int> *material_indices;
    mesh->GetMaterialIndices(&material_indices);




    for (int i = 0; i < mesh->GetPolygonCount(); i++)
    {
        material_mapped_indices[material_indices->GetAt(i)] << (unsigned int)(mesh->GetPolygonVertex(i, 0));
        material_mapped_indices[material_indices->GetAt(i)] << (unsigned int)(mesh->GetPolygonVertex(i, 1));
        material_mapped_indices[material_indices->GetAt(i)] << (unsigned int)(mesh->GetPolygonVertex(i, 2));
    }




    for (auto it : material_mapped_indices.keys())
    {


        master_indices << material_mapped_indices[it];


        DrawElementsCommand c;
        c.baseInstance = 0;
        c.instanceCount = 1;
        c.baseVertex = current_control_point_offset;
        c.firstIndex = current_polygon_offset;
        c.vertexCount = material_mapped_indices[it].size();
        commands[QString(mesh->GetNode()->GetMaterial(it)->GetName())] = c;
        current_polygon_offset += c.vertexCount;


    }



}



void MeshEntry::LoadTransform(FbxMesh *mesh)
{



    FbxAMatrix transform = mesh->GetNode()->GetParent()->EvaluateLocalTransform(0)
            * mesh->GetNode()->EvaluateLocalTransform(0);



    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            local_transform(i, j) = transform.Transpose().Get(i, j);




}


