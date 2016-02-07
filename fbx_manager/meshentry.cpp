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
    LoadTransform(mesh);



    vao.release();
    shader.release();




}




void MeshEntry::Draw(QOpenGLFunctions * f, QMap<QString, QOpenGLTexture *> &texture_cache, QOpenGLShaderProgram &shader)
{



    shader.setUniformValue("M", local_transform);




    vao.bind();



    if (textures.count("diffuse"))
    {
        texture_cache[textures["diffuse"]]->bind();
        shader.setUniformValue("use_diffuse_texture", true);
    }
    else
    {
        shader.setUniformValue("diffuse_color", colors["diffuse"]);
        shader.setUniformValue("use_diffuse_texture", false);
    }



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

            LoadDiffuseMaterial(material, shader, directory, texture_cache);

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



void MeshEntry::LoadTransform(FbxMesh *mesh)
{


    FbxAMatrix transform = mesh->GetNode()->GetParent()->EvaluateLocalTransform(0)
            * mesh->GetNode()->EvaluateLocalTransform(0);



    QVector3D base_scale = QVector3D(transform.GetS().mData[0],
            transform.GetS().mData[1],
            transform.GetS().mData[2]);
    QMatrix4x4 base_scale_matrix;
    base_scale_matrix.scale(QVector3D(1.0, 1.0, 1.0) / base_scale);



    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            local_transform(i, j) = transform.Transpose().Get(i, j);


    local_transform = base_scale_matrix * local_transform;




}



QString MeshEntry::ComputeTextureFilename(QString file_name, QString directory)
{


    file_name.replace("\\", "/");
    file_name = file_name.mid(file_name.lastIndexOf("/") + 1, file_name.length());
    if (directory.length() > 0)
        file_name = directory + "/" + file_name;



    return file_name;



}



void MeshEntry::LoadDiffuseMaterial(FbxSurfaceMaterial *material, QOpenGLShaderProgram &shader, QString directory, QMap<QString, QOpenGLTexture *> &texture_cache)
{


    FbxProperty diffuse_prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
    if (diffuse_prop.GetSrcObjectCount<FbxFileTexture>() > 0)
    {
        FbxFileTexture* texture = FbxCast<FbxFileTexture>(diffuse_prop.GetSrcObject<FbxFileTexture>(0));
        QString texture_index = ComputeTextureFilename(texture->GetFileName(), directory);


        if (QFileInfo(texture_index).exists())
        {
            textures["diffuse"] = texture_index;
            if (!texture_cache.count(texture_index))
            {

                QOpenGLTexture * diffuse_texture = new QOpenGLTexture(QImage(texture_index).mirrored());
                texture_cache[texture_index] = diffuse_texture;
                shader.setUniformValue("diffuse_texture", 0);

            }
        }
        else
        {
            qDebug() << "Can't find texture: " << texture_index << " in the .fbx folder!";
        }


    }



    colors["diffuse"] = QVector3D(diffuse_prop.Get<FbxDouble3>().mData[0],
            diffuse_prop.Get<FbxDouble3>().mData[1],
            diffuse_prop.Get<FbxDouble3>().mData[2]);







}



