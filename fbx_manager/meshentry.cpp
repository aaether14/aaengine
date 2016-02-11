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
                         int & current_control_point_offset,
                         int & current_polygon_offset)
{



    LoadVertices(mesh, master_vertices, current_control_point_offset);
    LoadIndices(mesh, master_indices, current_polygon_offset);
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



    current_control_point_offset += mesh->GetControlPointsCount() * 3;



}




void MeshEntry::LoadNormals(FbxMesh * mesh)
{


    //    if(mesh->GetElementNormalCount() < 1)
    //    {
    //        qDebug() << "Invalid normals!";
    //        return;
    //    }




    //    FbxGeometryElementNormal* vertex_normal = mesh->GetElementNormal(0);
    //    if (vertex_normal->GetMappingMode() == FbxGeometryElement::eByControlPoint)
    //    {


    //    }
    //    else
    //    {
    //        qDebug() << "Invalid normal format!";
    //    }




    //    QVector<float> normals;
    //    for (int i = 0; i < mesh->GetControlPointsCount(); i++)
    //    {


    //        normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[0]);
    //        normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[1]);
    //        normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[2]);



    //    }


    //    normals_vbo.create();
    //    normals_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //    normals_vbo.bind();
    //    normals_vbo.allocate(&normals[0], sizeof(float) * normals.size());



    //    shader.setAttributeBuffer("normal", GL_FLOAT, 0, 3);
    //    shader.enableAttributeArray("normal");



    //    normals.clear();






}





void MeshEntry::LoadMaterials(FbxMesh *mesh)
{



    //    for (int i = 0; i < mesh->GetNode()->GetSrcObjectCount<FbxSurfaceMaterial>(); i++)
    //    {

    //        FbxSurfaceMaterial *material = mesh->GetNode()->GetSrcObject<FbxSurfaceMaterial>(i);
    //        if (material)
    //        {

    //            LoadDiffuseMaterial(material, shader);

    //        }

    //    }



}








void MeshEntry::LoadUVs(FbxMesh *mesh)
{


    //    if (mesh->GetElementUVCount() < 1)
    //    {
    //        qDebug() << "Invalid UVs!";
    //        return;
    //    }



    //    FbxGeometryElementUV* vertex_uv = mesh->GetElementUV(0);
    //    if (vertex_uv->GetMappingMode() == FbxGeometryElement::eByControlPoint)
    //    {


    //    }
    //    else
    //    {
    //        qDebug() << "Invalid UV format!";
    //    }



    //    QVector<float> uvs;
    //    for (int i = 0; i < mesh->GetControlPointsCount(); i++)
    //    {


    //        uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[0]);
    //        uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[1]);


    //    }


    //    uvs_vbo.create();
    //    uvs_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //    uvs_vbo.bind();
    //    uvs_vbo.allocate(&uvs[0], sizeof(float) * uvs.size());



    //    shader.setAttributeBuffer("uv", GL_FLOAT, 0, 2);
    //    shader.enableAttributeArray("uv");



    //    uvs.clear();






}






void MeshEntry::LoadIndices(FbxMesh *mesh, QVector<unsigned int> &master_indices, int &current_polygon_offset)
{




    for (int i = 0; i < mesh->GetPolygonCount(); i++)
    {

        master_indices << (unsigned int)(mesh->GetPolygonVertex(i, 0));
        master_indices << (unsigned int)(mesh->GetPolygonVertex(i, 1));
        master_indices << (unsigned int)(mesh->GetPolygonVertex(i, 2));

    }



    current_polygon_offset += mesh->GetPolygonCount() * 3;





}



void MeshEntry::LoadTransform(FbxMesh *mesh)
{



    FbxAMatrix transform = mesh->GetNode()->GetParent()->EvaluateLocalTransform(0)
            * mesh->GetNode()->EvaluateLocalTransform(0);



    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            local_transform(i, j) = transform.Transpose().Get(i, j);




}





void MeshEntry::LoadDiffuseMaterial(FbxSurfaceMaterial *material)
{


    FbxProperty diffuse_prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);




}



