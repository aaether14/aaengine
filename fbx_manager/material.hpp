#ifndef MATERIAL_H
#define MATERIAL_H



#include <QVector3D>
#include <QOpenGLShaderProgram>




/**
 * @brief The Material class holds material data
 */
class Material
{



public:


    /**
     * @brief Material - basic constructor
     */
    Material();


    /**
     *@brief diffuse_color is the diffuse component of the material
     */
    QVector3D diffuse_color;
    /**
     *@brief ambient_color is the ambient component of the material
     */
    QVector3D ambient_color;
    /**
     *@brief emissive_color is the emissive component of the material
     */
    QVector3D emissive_color;
    /**
     *@brief difuse_texture_name is the name of the diffuse texture the
     *material is using
     */
    QString difuse_texture_name;
    /**
     *@brief use_diffuse_texture true if the material will use a diffuse
     *texture, fasle otherwise
     */
    bool use_diffuse_texture;

    /**
     * @brief SendToShader will send the material data to the shader
     * @param shader is the shader the material will sent to by uniforms
     */
    void SendToShader(QOpenGLShaderProgram & shader);



};




/**
 *@brief The DrawElementsCommand struct holdes information for a single draw
 *command
 */
struct DrawElementsCommand
{
    GLuint vertexCount;
    GLuint instanceCount;
    GLuint firstIndex;
    GLuint baseVertex;
    GLuint baseInstance;
};











#endif // MATERIAL_H
