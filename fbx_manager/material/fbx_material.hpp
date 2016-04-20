#ifndef MATERIAL_H
#define MATERIAL_H



#include <aae_defines.hpp>



#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QFileInfo>
#include <QDataStream>



#include <fbx_manager/mesh_util.hpp>



#ifdef AAE_USING_FBX
#include <fbxsdk.h>
#endif






/**
 * @brief The Material class holds material data
 */
class Material
{




    /**
     *@brief diffuse_color is the diffuse component of the material
     */
    QVector3D m_diffuse_color;




    /**
     *@brief textures is a hash containing the name of the textures used by the
     *material
     */
    QHash<quint32, QString> m_textures;






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
     * @brief SendToShader will send the material data to the shader
     * @param shader is the shader the material will sent to by uniforms
     */
    void SendToShader(QOpenGLShaderProgram &shader);




#ifdef AAE_USING_FBX


    /**
     * @brief AddProperty will add a certain property to the material
     * @param property is the property to be added
     */
    void AddProperty(const FbxProperty &property);

#endif



    /**
     * @brief GetDiffuseColor will get the diffuse color of the material
     * @return m_diffuse_color
     */
    inline const QVector3D & GetDiffuseColor() const{
        return m_diffuse_color;
    }



    /**
     * @brief GetTextures will get the textures of the material
     * @return m_textures
     */
    inline const QHash<quint32, QString> & GetTextures() const{
        return m_textures;
    }



    /**
     * @brief SetDiffuseColor will set the diffuse color of the material
     * @param diffuse_color is the color to update diffuse color
     */
    inline void SetDiffuseColor(const QVector3D & diffuse_color){
        m_diffuse_color = diffuse_color;
    }



    /**
     * @brief SetTextures will set the textures of the material
     * @param textures is the texture has to update materials' textures
     */
    inline void SetTextures(const QHash<quint32, QString> & textures){
        m_textures = textures;
    }





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
