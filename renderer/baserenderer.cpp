#include <renderer/baserenderer.hpp>




void BaseRenderer::AddShader(QString shader_name, QOpenGLShaderProgram *shader)
{


    shaders[shader_name] = shader;


}



QOpenGLShaderProgram *BaseRenderer::GetShader(QString shader_name)
{

    return shaders[shader_name];

}



BaseRenderer::BaseRenderer()
{



}



BaseRenderer::~BaseRenderer()
{


    qDeleteAll(shaders);


}
