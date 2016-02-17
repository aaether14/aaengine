#include <renderer/fbxrenderer.hpp>




FbxRenderer::FbxRenderer()
{




    QOpenGLShaderProgram fbx_shader;
    fbx_shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/fbx_render.vert");
    fbx_shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fbx_render.frag");
    fbx_shader.link();


    AddShader("Fbx", &fbx_shader);



}



void FbxRenderer::Render(QObject *parent)
{


    GetShader("Fbx")->bind();
    GetShader("Fbx")->release();




}



