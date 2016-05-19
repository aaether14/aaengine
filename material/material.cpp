#include <material/material.hpp>





Material::Material() : m_diffuse_color(),
    m_diffuse_intensity(0.0),
    m_specular_color(),
    m_specular_intensity(0.0),
    m_specular_hardness(0.0)
{


    /**
    *The glorious nothing...
    */


}




void Material::SendUniformsToShader(QOpenGLShaderProgram &shader)
{


    /**
    *Diffuse component
    */
    shader.setUniformValue("diffuse_color", m_diffuse_color);
    shader.setUniformValue("diffuse_intensity", m_diffuse_intensity);
    shader.setUniformValue("use_diffuse_texture", m_textures.contains(diffuse));


    /**
    *Specular component
    */
    shader.setUniformValue("specular_color", m_specular_color);
    shader.setUniformValue("specular_intensity", m_specular_intensity);
    shader.setUniformValue("specular_hardness", m_specular_hardness);


}





QDataStream &operator <<(QDataStream &out, const Material &material)
{


    /**
    *Output material data to data stream
    */
    out << material.GetDiffuseColor() <<  material.GetDiffuseIntensity();
    out << material.GetSpecularColor() << material.GetSpecularIntensity() << material.GetSpecularHardness();
    out << material.GetTextures();
    return out;


}



QDataStream &operator >>(QDataStream &in, Material &material)
{


    /**
     *We will temporarily store data in this variables
     */



    /**
     *Diffuse component
     */
    float diffuse_intensity;
    QVector3D diffuse_color;


    /**
     *Specular component
     */
    float specular_intensity;
    float specular_hardness;
    QVector3D specular_color;


    /**
     *Material's textures
     */
    QHash<quint32, QString> textures;



    /**
    *Load material data
    */
    in >> diffuse_color >> diffuse_intensity;
    in >> specular_color >> specular_intensity >> specular_hardness;
    in >> textures;



    /**
    *Set material data
    */
    material.SetDiffuseIntensity(diffuse_intensity);
    material.SetDiffuseColor(diffuse_color);
    material.SetSpecularColor(specular_color);
    material.SetSpecularIntensity(specular_intensity);
    material.SetSpecularHardness(specular_hardness);
    material.SetTextures(textures);



    return in;



}










