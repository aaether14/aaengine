#include <fbx_manager/meshentry.hpp>






MeshEntry::MeshEntry() : ibo(QOpenGLBuffer::IndexBuffer),
    vertices_vbo(QOpenGLBuffer::VertexBuffer),
    normals_vbo(QOpenGLBuffer::VertexBuffer),
    uvs_vbo(QOpenGLBuffer::VertexBuffer)
{



}






MeshEntry::~MeshEntry()
{




}





void MeshEntry::LoadMesh(FbxMesh * mesh, QOpenGLShaderProgram & shader)
{




    vao.create();
    vao.bind();
    shader.bind();


    LoadVertices(mesh, shader);
    LoadNormals(mesh, shader);
    LoadMaterials(mesh, shader);
    LoadUVs(mesh, shader);
    LoadIndices(mesh);



    vao.release();
    shader.release();





}




void MeshEntry::Draw(QOpenGLFunctions * f)
{


    vao.bind();
    material_texture->bind();
    f->glDrawElements(GL_TRIANGLES, tri_count, GL_UNSIGNED_INT, 0);
    vao.release();


}






void MeshEntry::LoadVertices(FbxMesh * mesh, QOpenGLShaderProgram & shader)
{



    QVector<float> vertices;
    for (int i = 0; i < mesh->GetControlPointsCount(); i++)
    {
        vertices << (float)(mesh->GetControlPointAt(i).mData[0]);
        vertices << (float)(mesh->GetControlPointAt(i).mData[1]);
        vertices << (float)(mesh->GetControlPointAt(i).mData[2]);
    }




    vertices_vbo.create();
    vertices_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertices_vbo.bind();
    vertices_vbo.allocate(&vertices[0], sizeof(float) * vertices.size());


    shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
    shader.enableAttributeArray("vertex");



    vertices.clear();




}




void MeshEntry::LoadNormals(FbxMesh * mesh, QOpenGLShaderProgram & shader)
{


    if(mesh->GetElementNormalCount() < 1)
    {
        qDebug() << "Invalid normals!";
    }




    FbxGeometryElementNormal* vertex_normal = mesh->GetElementNormal(0);
    if (vertex_normal->GetMappingMode() == FbxGeometryElement::eByControlPoint)
    {


    }
    else
    {


    }




    QVector<float> normals;
    for (int i = 0; i < mesh->GetControlPointsCount(); i++)
    {


        normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[0]);
        normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[1]);
        normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[2]);



    }


    normals_vbo.create();
    normals_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    normals_vbo.bind();
    normals_vbo.allocate(&normals[0], sizeof(float) * normals.size());



    shader.setAttributeBuffer("normal", GL_FLOAT, 0, 3);
    shader.enableAttributeArray("normal");



    normals.clear();






}





void MeshEntry::LoadMaterials(FbxMesh *mesh, QOpenGLShaderProgram &shader)
{




    for (int i = 0; i < mesh->GetNode()->GetSrcObjectCount<FbxSurfaceMaterial>(); i++)
    {



        FbxSurfaceMaterial *material = mesh->GetNode()->GetSrcObject<FbxSurfaceMaterial>(i);
        if (material)
        {


            FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
            for (int j = 0; j < prop.GetSrcObjectCount<FbxFileTexture>(); j++)
            {


                FbxFileTexture* texture = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxFileTexture>(j));
                qDebug() << texture->GetFileName();
                QString texture_filename = QString(texture->GetFileName());
                texture_filename = texture_filename.mid(texture_filename.lastIndexOf("\\") + 1, texture_filename.length());


                material_texture = new QOpenGLTexture(QImage(texture_filename).mirrored());
                shader.setUniformValue("material_texture", 0);



                break;

            }


        }



    }


}





void MeshEntry::LoadUVs(FbxMesh *mesh, QOpenGLShaderProgram &shader)
{


    if (mesh->GetElementUVCount() < 1)
    {
        qDebug() << "Invalid UVs!";
    }



    FbxGeometryElementUV* vertex_uv = mesh->GetElementUV(0);
    if (vertex_uv->GetMappingMode() == FbxGeometryElement::eByControlPoint)
    {


    }
    else
    {


    }



    QVector<float> uvs;
    for (int i = 0; i < mesh->GetControlPointsCount(); i++)
    {


        uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[0]);
        uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[1]);


    }


    uvs_vbo.create();
    uvs_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    uvs_vbo.bind();
    uvs_vbo.allocate(&uvs[0], sizeof(float) * uvs.size());



    shader.setAttributeBuffer("uv", GL_FLOAT, 0, 2);
    shader.enableAttributeArray("uv");



    uvs.clear();






}






void MeshEntry::LoadIndices(FbxMesh *mesh)
{




    QVector<unsigned int> indices;
    for (int i = 0; i < mesh->GetPolygonCount(); i++)
    {

        indices << (unsigned int)(mesh->GetPolygonVertex(i, 0));
        indices << (unsigned int)(mesh->GetPolygonVertex(i, 1));
        indices << (unsigned int)(mesh->GetPolygonVertex(i, 2));


    }
    tri_count = indices.size();



    ibo.create();
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.bind();
    ibo.allocate(&indices[0], sizeof(unsigned int) * indices.size());




}



