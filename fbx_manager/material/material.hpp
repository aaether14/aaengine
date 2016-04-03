#ifndef MATERIAL_H
#define MATERIAL_H



#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QFileInfo>


#include <fbx_manager/mesh_util.hpp>
#include <fbxsdk.h>




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
     *@brief emissive_color is the emissive component of the material
     */
    QVector3D emissive_color;
    /**
     *@brief difuse_texture_name is the name of the diffuse texture the
     *material is using
     */
    QString difuse_texture_name;
    /**
     *@brief use_diffuse_texture is true if the material will use a diffuse
     *texture, fasle otherwise
     */
    bool use_diffuse_texture;
    /**
     *@brief normal_map_name is the name of the normal map the material is
     *using
     */
    QString normal_map_name;
    /**
     *@brief use_normal_map is true if the material will use a normal map,
     *false otherwise
     */
    bool use_normal_map;


    /**
     * @brief SendToShader will send the material data to the shader
     * @param shader is the shader the material will sent to by uniforms
     */
    void SendToShader(QOpenGLShaderProgram & shader);


    /**
     * @brief AddDiffuseProperty will add diffuse property to the material
     * @param diffuse_property is the property to be added
     * @param textures is the texture hash of the 3d mesh
     * @param fbx_file_name is the name of the fbx mesh
     */
    void AddDiffuseProperty(FbxProperty diffuse_property,
                            QHash<QString, QImage> & images,
                            QString fbx_file_name);



    /**
     * @brief AddNormalProperty will add normal property to the material
     * @param normal_property is the property to be added
     * @param textures is the texture hash of the 3d mesh
     * @param fbx_file_name is the name of the fbx mesh
     */
    void AddNormalProperty(FbxProperty normal_property,
                           QHash<QString, QImage> & images,
                           QString fbx_file_name);



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
