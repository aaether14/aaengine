#include <fbx_manager/material/fbx_material.hpp>





Material::Material() : m_diffuse_color()
{



}




void Material::SendToShader(QOpenGLShaderProgram &shader)
{


    shader.setUniformValue("diffuse_color", m_diffuse_color);
    shader.setUniformValue("use_diffuse_texture", m_textures.contains(diffuse));


}




#ifdef AAE_USING_FBX
void Material::AddProperty(const FbxProperty &property)
{




    /**
    *If we are dealing with an invalid property, return;
    */
    if (!property.IsValid())
        return;



    QString property_name = property.GetNameAsCStr();
    if (property_name == FbxSurfaceMaterial::sDiffuse)
    {



        FbxDouble3 diffuse_color = property.Get<FbxDouble3>();
        SetDiffuseColor(aae::mesh_util::QVector3DFromFbxVector3D(diffuse_color));



        /**
        *If there are no textures attached to the property, return
        */
        if(!property.GetSrcObjectCount<FbxFileTexture>() > 0)
            return;



        FbxFileTexture * texture = property.GetSrcObject<FbxFileTexture>();
        if (!texture)
            return;



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





}
#endif




QDataStream &operator <<(QDataStream &out, const Material &material)
{


    out << material.GetDiffuseColor() << material.GetTextures();
    return out;


}



QDataStream &operator >>(QDataStream &in, Material &material)
{

    QVector3D diffuse_color;
    QHash<quint32, QString> textures;


    in>>diffuse_color >> textures;
    material.SetDiffuseColor(diffuse_color);
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





