#include <fbx_manager/material/fbx_material.hpp>





Material::Material() : diffuse_color(QVector3D(0, 0, 0))
{



}



void Material::SendToShader(QOpenGLShaderProgram &shader)
{


    shader.setUniformValue("diffuse_color", diffuse_color);
    shader.setUniformValue("use_diffuse_texture", textures.contains(diffuse));


}




void Material::AddDiffuseProperty(FbxProperty diffuse_property)
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




    textures[diffuse] = texture->GetFileName();




}





void Material::AddNormalProperty(FbxProperty normal_property)
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





    textures[normal] = texture->GetFileName();





}






QDataStream &operator <<(QDataStream &out, const Material &material)
{


    out << material.diffuse_color << material.textures;
    return out;


}



QDataStream &operator >>(QDataStream &in, Material &material)
{

    in >> material.diffuse_color >> material.textures;
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





