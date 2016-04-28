#include <renderer/baserenderer.hpp>




void BaseRenderer::AddShader(const QString &shader_name,
                             QOpenGLShaderProgram *shader)
{


    /**
    *Insert the new shader in the shader hash
    */
    shaders.insert(shader_name, shader);

}



QOpenGLShaderProgram * BaseRenderer::GetShader(const QString &shader_name)
{

    /**
    *Get the shader stored with the provided key
    */
    return shaders.value(shader_name);

}
\


BaseRenderer::BaseRenderer()
{


    /**
    *The glorious nothing...
    */


}



BaseRenderer::~BaseRenderer()
{


    /**
     *Delete the shaders and the shader hash
     */
    qDeleteAll(shaders);
    shaders.clear();


}
