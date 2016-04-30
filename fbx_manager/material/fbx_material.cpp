#include <fbx_manager/material/fbx_material.hpp>





Material::Material() : m_diffuse_color(),
    m_diffuse_intensity(0.0),
    m_specular_color(),
    m_specular_intensity(0.0),
    m_specular_hardness(0.0)
{


    /**
    *The glorious nothing...
    */


}




void Material::SendToShader(QOpenGLShaderProgram &shader)
{


    /**
    *Diffuse component
    */
    shader.setUniformValue("diffuse_color", m_diffuse_color);
    shader.setUniformValue("diffuse_intensity", m_diffuse_intensity);
    shader.setUniformValue("use_diffuse_texture", m_textures.contains(diffuse));


    /**
    *Specular component
    */
    shader.setUniformValue("specular_color", m_specular_color);
    shader.setUniformValue("specular_intensity", m_specular_intensity);
    shader.setUniformValue("specular_hardness", m_specular_hardness);


}




#ifdef AAE_USING_FBX
void Material::AddProperty(const FbxProperty &property,
                           const FbxProperty &factor_property)
{




    /**
    *If we are dealing with an invalid properties, abort
    */
    if (!property.IsValid() || !factor_property.IsValid())
        return;




    /**
     *Get the name of the property
     */
    QString property_name = property.GetNameAsCStr();


    /**
    *Based on the property's name, load required stuff
    */
    if (property_name == FbxSurfaceMaterial::sDiffuse)
    {



        /**
         *Get the diffuse color and intensity
         */
        FbxDouble3 diffuse_color = property.Get<FbxDouble3>();
        FbxDouble diffuse_intensity = factor_property.Get<FbxDouble>();



        /**
         *Set diffuse color and intensity
         */
        SetDiffuseColor(aae::mesh_util::QVector3DFromFbxVector3D(diffuse_color));
        SetDiffuseIntensity(diffuse_intensity);




        /**
        *If there are no textures attached to the property, return
        */
        if(!property.GetSrcObjectCount<FbxFileTexture>() > 0)
            return;



        /**
         *Get the texture handler
         */
        FbxFileTexture * texture = property.GetSrcObject<FbxFileTexture>();
        if (!texture)
            return;



        /**
        *Add the diffuse texture name of the material
        */
        m_textures[diffuse] = texture->GetFileName();


    }
    else if (property_name == FbxSurfaceMaterial::sNormalMap)
    {


        /**
        *If there are no textures attached to the property, return
        */
        if(!property.GetSrcObjectCount<FbxFileTexture>() > 0)
            return;



        FbxFileTexture * texture = property.GetSrcObject<FbxFileTexture>();
        if (!texture)
            return;



        m_textures[normal] = texture->GetFileName();


    }
    else if (property_name == FbxSurfaceMaterial::sSpecular)
    {


        /**
         *Get the specular color and intensity
         */
        FbxDouble3 specular_color = property.Get<FbxDouble3>();
        FbxDouble specular_intensity = factor_property.Get<FbxDouble>();



        /**
        *Set the specular color and intensity
        */
        SetSpecularColor(aae::mesh_util::QVector3DFromFbxVector3D(specular_color));
        SetSpecularIntensity(specular_intensity);



    }
    else if (property_name == FbxSurfaceMaterial::sShininess)
    {


        /**
         *Get and set specular hardness
         */
        FbxDouble specular_hardness = property.Get<FbxDouble>();
        SetSpecularHardness(specular_hardness);


    }





}
#endif




QDataStream &operator <<(QDataStream &out, const Material &material)
{


    /**
    *Output material data to data stream
    */
    out << material.GetDiffuseColor() <<  material.GetDiffuseIntensity();
    out << material.GetSpecularColor() << material.GetSpecularIntensity() << material.GetSpecularHardness();
    out << material.GetTextures();
    return out;


}



QDataStream &operator >>(QDataStream &in, Material &material)
{


    /**
     *We will temporarily store data in this variables
     */



    /**
     *Diffuse component
     */
    float diffuse_intensity;
    QVector3D diffuse_color;


    /**
     *Specular component
     */
    float specular_intensity;
    float specular_hardness;
    QVector3D specular_color;


    /**
     *Material's textures
     */
    QHash<quint32, QString> textures;



    /**
    *Load material data
    */
    in >> diffuse_color >> diffuse_intensity;
    in >> specular_color >> specular_intensity >> specular_hardness;
    in >> textures;



    /**
    *Set material data
    */
    material.SetDiffuseIntensity(diffuse_intensity);
    material.SetDiffuseColor(diffuse_color);
    material.SetSpecularColor(specular_color);
    material.SetSpecularIntensity(specular_intensity);
    material.SetSpecularHardness(specular_hardness);
    material.SetTextures(textures);



    return in;



}





QDataStream &operator <<(QDataStream &out, const DrawElementsCommand &command)
{


    out << command.baseInstance << command.baseVertex << command.firstIndex;
    out << command.instanceCount << command.vertexCount;
    return out;


}



QDataStream &operator >>(QDataStream &in, DrawElementsCommand &command)
{


    in >> command.baseInstance >> command.baseVertex >> command.firstIndex;
    in >> command.instanceCount >> command.vertexCount;
    return in;


}





