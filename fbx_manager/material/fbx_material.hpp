#ifndef MATERIAL_H
#define MATERIAL_H



#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QFileInfo>
#include <QDataStream>



#include <fbx_manager/mesh_util.hpp>
#include <fbxsdk.h>







/**
 * @brief The Material class holds material data
 */
class Material
{



public:




    enum texture_types
    {
        diffuse,
        normal,
        number_of_texture_types
    };



    /**
     * @brief Material - basic constructor
     */
    Material();


    /**
     *@brief diffuse_color is the diffuse component of the material
     */
    QVector3D diffuse_color;




    /**
     *@brief textures is a hash containing the name of the textures used by the
     *material
     */
    QHash<quint32, QString> textures;



    /**
     * @brief SendToShader will send the material data to the shader
     * @param shader is the shader the material will sent to by uniforms
     */
    void SendToShader(QOpenGLShaderProgram &shader);



    /**
     * @brief AddDiffuseProperty will add the diffuse property of the material
     * @param diffuse_property is the property to be added
     */
    void AddDiffuseProperty(FbxProperty diffuse_property);




    /**
     * @brief AddNormalProperty will add the normal map property of the material
     * @param normal_property is the property to be added
     */
    void AddNormalProperty(FbxProperty normal_property);



};




/**
 *@brief The DrawElementsCommand struct holdes information for a single draw
 *command
 */
struct DrawElementsCommand
{
    quint32 vertexCount;
    quint32 instanceCount;
    quint32 firstIndex;
    quint32 baseVertex;
    quint32 baseInstance;
};




QDataStream &operator <<(QDataStream &out, const DrawElementsCommand &command);
QDataStream &operator >>(QDataStream &in, DrawElementsCommand &command);
QDataStream &operator <<(QDataStream &out, const Material &material);
QDataStream &operator >>(QDataStream &in, Material &material);




#endif // MATERIAL_H
