#include <fbx_manager/material/material.hpp>





Material::Material() : diffuse_color(QVector3D(0, 0, 0)),
    ambient_color(QVector3D(0, 0, 0)),
    emissive_color(QVector3D(0, 0, 0)),
    difuse_texture_name(QString()),
    use_diffuse_texture(false)
{



}



void Material::SendToShader(QOpenGLShaderProgram &shader)
{


    shader.setUniformValue("diffuse_color", diffuse_color);
    shader.setUniformValue("use_diffuse_texture", use_diffuse_texture);


}




void Material::AddDiffuseProperty(FbxProperty diffuse_property,
                                  QHash<QString, QOpenGLTexture *> &textures,
                                  QString fbx_file_name)
{




    /**
     * Get the diffuse color of the material
     */


    FbxDouble3 diffuse_color = diffuse_property.Get<FbxDouble3>();
    this->diffuse_color = QVector3D(diffuse_color.mData[0], diffuse_color.mData[1], diffuse_color.mData[2]);



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
    if (!textures.contains(texture_index))
        textures[texture_index] = new QOpenGLTexture(QImage(texture_index).mirrored());




    this->difuse_texture_name = texture_index;
    this->use_diffuse_texture = true;






}




