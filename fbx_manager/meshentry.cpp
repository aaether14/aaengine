#include <fbx_manager/meshentry.hpp>






MeshEntry::MeshEntry() : ibo(QOpenGLBuffer::IndexBuffer),
    vertices_vbo(QOpenGLBuffer::VertexBuffer),
    normals_vbo(QOpenGLBuffer::VertexBuffer),
    uvs_vbo(QOpenGLBuffer::VertexBuffer)
{



}






MeshEntry::~MeshEntry()
{


    ibo.destroy();
    vertices_vbo.destroy();
    normals_vbo.destroy();
    uvs_vbo.destroy();
    vao.destroy();


}





void MeshEntry::LoadMesh(FbxMesh * mesh, QOpenGLShaderProgram & shader, QString directory, QMap<QString, QOpenGLTexture *> &texture_cache)
{




    vao.create();
    vao.bind();
    shader.bind();



    LoadVertices(mesh, shader);
    LoadNormals(mesh, shader);
    LoadUVs(mesh, shader);
    LoadIndices(mesh);
    LoadMaterials(mesh, shader, directory, texture_cache);



    vao.release();
    shader.release();





}




void MeshEntry::Draw(QOpenGLFunctions * f, QMap<QString, QOpenGLTexture *> &texture_cache)
{


    vao.bind();



    if (textures.count("diffuse"))
        texture_cache[textures["diffuse"]]->bind();



    f->glDrawElements(GL_TRIANGLES, tri_count, GL_UNSIGNED_INT, 0);



    if (textures.count("diffuse"))
        texture_cache[textures["diffuse"]]->release();



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





void MeshEntry::LoadMaterials(FbxMesh *mesh, QOpenGLShaderProgram &shader, QString directory, QMap<QString, QOpenGLTexture *> &texture_cache)
{



    for (int i = 0; i < mesh->GetNode()->GetSrcObjectCount<FbxSurfaceMaterial>(); i++)
    {



        FbxSurfaceMaterial *material = mesh->GetNode()->GetSrcObject<FbxSurfaceMaterial>(i);
        if (material)
        {



            FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
            if (prop.GetSrcObjectCount<FbxFileTexture>() > 0)
            {
                FbxFileTexture* texture = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxFileTexture>(0));
                QString texture_index = ComputeTextureFilename(texture->GetFileName(), directory);


                if (QFileInfo(texture_index).exists())
                {
                    textures["diffuse"] = texture_index;
                    if (!texture_cache.count(texture_index))
                    {

                        QOpenGLTexture * diffuse_texture = new QOpenGLTexture(QImage(texture_index).mirrored());
                        texture_cache[texture_index] = diffuse_texture;
                        shader.setUniformValue("material_texture", 0);

                    }
                }



            }

        }



    }


}





void MeshEntry::LoadUVs(FbxMesh *mesh, QOpenGLShaderProgram &shader)
{


    if (mesh->GetElementUVCount() < 1)
    {
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



QString MeshEntry::ComputeTextureFilename(QString file_name, QString directory)
{


    file_name.replace("\\", "/");
    file_name = file_name.mid(file_name.lastIndexOf("/") + 1, file_name.length());
    if (directory.length() > 0)
        file_name = directory + "/" + file_name;



    return file_name;



}



