#ifndef MATERIAL_H
#define MATERIAL_H



#include <QVector3D>
#include <QOpenGLShaderProgram>



class Material
{



public:
    Material();



    QVector3D diffuse_color;
    QString difuse_texture_name;
    bool use_diffuse_texture;


    void SendToShader(QOpenGLShaderProgram & shader);



};





struct DrawElementsCommand
{
  GLuint vertexCount;
  GLuint instanceCount;
  GLuint firstIndex;
  GLuint baseVertex;
  GLuint baseInstance;
};











#endif // MATERIAL_H
