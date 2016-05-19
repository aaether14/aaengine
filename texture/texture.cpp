#include <texture/texture.hpp>




Texture::~Texture()
{

    /**
    *Release texture data
    */
    ReleaseImages();

}



void Texture::ReleaseImages()
{

    m_images.clear();

}



void Texture::GenerateMipmaps()
{

}




QDataStream &operator <<(QDataStream &out, const Texture &texture)
{

    out << texture.GetImages();
    return out;

}
