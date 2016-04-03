#include <fbx_manager/material/material.hpp>





Material::Material() : diffuse_color(QVector3D(0, 0, 0)),
    emissive_color(QVector3D(0, 0, 0)),
    difuse_texture_name(QString()),
    use_diffuse_texture(false),
    normal_map_name(QString()),
    use_normal_map(false)
{



}



void Material::SendToShader(QOpenGLShaderProgram &shader)
{


    shader.setUniformValue("diffuse_color", diffuse_color);
    shader.setUniformValue("use_diffuse_texture", use_diffuse_texture);


}




void Material::AddDiffuseProperty(FbxProperty diffuse_property,
                                  QHash<QString, QImage> &images,
                                  QString fbx_file_name)
{



    /**
    *If we are dealing with an invalid property, return;
    */


    if (!diffuse_property.IsValid())
        return;



    /**
     * Get the diffuse color of the material
     */


    FbxDouble3 diffuse_color = diffuse_property.Get<FbxDouble3>();
    this->diffuse_color = aae::mesh_util::QVector3DFromFbxVector3D(diffuse_color);



    /**
    *If there are no textures attached to the property, return
    */


    if(!diffuse_property.GetSrcObjectCount<FbxFileTexture>() > 0)
        return;



    FbxFileTexture * texture = diffuse_property.GetSrcObject<FbxFileTexture>();
    if (!texture)
        return;



    /**
     *texture_index is the index by which this texture will be stored and it's
     *the path of the texture
     */



    QString texture_index = aae::mesh_util::ComputeTextureFilename(texture->GetFileName(),
                                                                   fbx_file_name);




    if (!QFileInfo(texture_index).exists())
    {
        qDebug() << "Could not find" << texture->GetFileName() <<"!";
        return;
    }




    /**
    *If the texture is not in the library, add it
    */
    if (!images.contains(texture_index))
        images[texture_index] = QImage(texture_index).mirrored();




    this->difuse_texture_name = texture_index;
    this->use_diffuse_texture = true;






}





void Material::AddNormalProperty(FbxProperty normal_property,
                                 QHash<QString, QImage> &images,
                                 QString fbx_file_name)
{



    /**
    *If we are dealing with an invalid property, return;
    */


    if (!normal_property.IsValid())
        return;



    /**
    *If there are no textures attached to the property, return
    */



    if(!normal_property.GetSrcObjectCount<FbxFileTexture>() > 0)
        return;



    FbxFileTexture * texture = normal_property.GetSrcObject<FbxFileTexture>();
    if (!texture)
        return;



    /**
     *texture_index is the index by which this texture will be stored and it's
     *the path of the texture
     */



    QString texture_index = aae::mesh_util::ComputeTextureFilename(texture->GetFileName(),
                                                                   fbx_file_name);




    if (!QFileInfo(texture_index).exists())
    {
        qDebug() << "Could not find" << texture->GetFileName() <<"!";
        return;
    }




    /**
    *If the texture is not in the library, add it
    */
    if (!images.contains(texture_index))
        images[texture_index] = QImage(texture_index).mirrored();




    this->normal_map_name = texture_index;
    this->use_normal_map = true;





}




