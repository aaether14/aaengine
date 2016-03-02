#include <fbx_manager/material.hpp>



Material::Material() : diffuse_color(QVector3D(0, 0, 0)),
    difuse_texture_name(""),
    use_diffuse_texture(false)
{

}



void Material::SendToShader(QOpenGLShaderProgram &shader)
{


    shader.setUniformValue("diffuse_color", diffuse_color);
    shader.setUniformValue("use_diffuse_texture", use_diffuse_texture);


}
