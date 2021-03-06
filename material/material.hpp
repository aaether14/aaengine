#ifndef MATERIAL_H
#define MATERIAL_H




#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QFileInfo>
#include <QDataStream>






class Material
{



    /**
     *@brief diffuse_color is the diffuse color of the material
     */
    QVector3D m_diffuse_color;


    /**
     * @brief m_diffuse_intensity is the diffuse intensity of the material
     */
    float m_diffuse_intensity;



    /**
     * @brief m_specular_color is the specular color of the material
     */
    QVector3D m_specular_color;


    /**
     * @brief m_specular_intensity is the specular intensity of the material
     */
    float m_specular_intensity;


    /**
     * @brief m_specular_hardness is the specular hardness of the material
     */
    float m_specular_hardness;



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
     * @brief Material is a nothing constructor
     */
    Material();



    /**
     * @brief SendToShader will send the material data to the shader
     * @param shader is the shader the material will sent to by uniforms
     */
    void SendUniformsToShader(QOpenGLShaderProgram &shader);



    /**
     * @brief AddTexture will add a certain texture to the texture hash
     * @param target is the type of the texture
     * @param texture_name is the name of the texture
     */
    inline void AddTexture(const quint32 &target,
                           const QString &texture_name){
        m_textures.insert(target, texture_name);

    }


    /**
     * @brief GetDiffuseColor will get the diffuse color of the material
     * @return m_diffuse_color
     */
    inline const QVector3D & GetDiffuseColor() const{
        return m_diffuse_color;
    }


    /**
     * @brief GetDiffuseIntensity will get the diffuse intensity of the material
     * @return m_diffuse_intensity
     */
    inline const float &GetDiffuseIntensity() const{
        return m_diffuse_intensity;
    }



    /**
     * @brief GetSpecularColor will get the specular color of the material
     * @return m_specular_color
     */
    inline const QVector3D & GetSpecularColor() const{
        return m_specular_color;
    }


    /**
     * @brief GetSpecularIntensity will get the specular intensity of the material
     * @return m_specular_intensity
     */
    inline const float & GetSpecularIntensity() const{
        return m_specular_intensity;
    }



    /**
     * @brief GetSpecularHardness will get the specular hardness of the material
     * @return m_specular_hardness
     */
    inline const float & GetSpecularHardness() const{
        return m_specular_hardness;
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
    inline void SetDiffuseColor(const QVector3D &diffuse_color){
        m_diffuse_color = diffuse_color;
    }


    /**
     * @brief SetDiffuseIntensity will set the diffuse intensity of the material
     * @param diffuse_intensity is the new diffuse intensity
     */
    inline void SetDiffuseIntensity(const float &diffuse_intensity){
        m_diffuse_intensity = diffuse_intensity;
    }



    /**
     * @brief SetSpecularColor will set the specular color of the material
     * @param specular_color is the new specular color
     */
    inline void SetSpecularColor(const QVector3D &specular_color){
        m_specular_color = specular_color;
    }


    /**
     * @brief SetSpecularIntensity will set the specular intensity of the material
     * @param specular_intensity is the new specular intensity
     */
    inline void SetSpecularIntensity(const float &specular_intensity){
        m_specular_intensity = specular_intensity;
    }



    /**
     * @brief SetSpecularHardness will set the specular hardness of the material
     * @param specular_hardness is the new specular hardness
     */
    inline void SetSpecularHardness(const float &specular_hardness){
        m_specular_hardness = specular_hardness;
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
*Serialization and deserialization routines
 */
QDataStream &operator <<(QDataStream &out, const Material &material);
QDataStream &operator >>(QDataStream &in, Material &material);




#endif // MATERIAL_H
