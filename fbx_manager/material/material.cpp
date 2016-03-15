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




QVector3D Material::FbxPropertyToVector3(FbxProperty prop)
{


    return QVector3D(prop.Get<FbxDouble3>().mData[0],
            prop.Get<FbxDouble3>().mData[1],
            prop.Get<FbxDouble3>().mData[2]);


}
