#ifndef TEXTURE_H
#define TEXTURE_H



#include <QOpenGLFunctions_4_3_Core>
#include <QDataStream>
#include <QVector>
#include <QImage>



#include <core/globalsettings.hpp>



/**
 * @brief The Texture class will hold texture information
 */
class Texture
{

    /**
     * @brief m_images will hold texture data
     */
    QVector<QImage> m_images;


public:

    /**
    *@brief Texture is a default constructor
    */
    Texture() = default;

    /**
    *@brief ~Texture will release texture data
    */
    virtual ~Texture();

    /**
     * @brief ReleaseImages will release texture data in m_images
     */
    virtual void ReleaseImages();

    /**
     *@brief GenerateMipmaps will attempt to generate mipmaps for the texture
     */
    virtual void GenerateMipmaps();

    /**
     * @brief GetImages will get the images used by the texture
     * @return m_images
     */
    inline const QVector<QImage> & GetImages() const{
        return m_images;
    }


};



/**
*Serialization and deserialization routines
 */
QDataStream &operator <<(QDataStream &out, const Texture &texture);
QDataStream &operator >>(QDataStream &in, Texture &texture);


#endif // TEXTURE_H
