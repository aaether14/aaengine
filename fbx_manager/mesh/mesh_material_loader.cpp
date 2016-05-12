#include <fbx_manager/mesh/mesh.hpp>





#ifdef AAE_USING_FBX
void Mesh::FBX_CommandLoadingMaterials()
{





    MaterialLoader * material_loader = new MaterialLoader(m_materials,
                                                          m_scene);



    material_loader->Load();
    delete material_loader;



}
#endif




void Mesh::LoadTextures()
{





    foreach(auto current_material, m_materials)
        foreach(auto current_texture, current_material.GetTextures().values())
            if (!d_images.contains(current_texture))
            {


                /**
                 *Get the path of the required texture
                 */
                QString texture_index = aae::mesh_util::ComputeTextureFilename(current_texture, GetFileName());


                /**
                *If texture does not exist, go on
                */
                if (!QFileInfo(texture_index).exists())
                {
                    qDebug() << "Could not find texture:" << current_texture << "!";
                    continue;
                }



                /**
                *Add the new texture to the library
                */
                d_images.insert(current_texture, QImage(texture_index).mirrored());

            }





}





void Mesh::PassTextureDataToOpenGL()
{



    /**
     * get opengl 4.3 functions from context
     */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();



    /**
    *Load textures into opengl memory
    */
    foreach(auto image_key, d_images.keys())
    {




        /**
         *Get the current image to be added as a texture
         */
        const QImage & current_image = d_images.value(image_key);



        /**
         *Sync object will be used to avoid stuttering
         */
        GLsync sync_obj;



        /**
         *Generate texture and add data to it
         */
        GLuint new_texture_id;
        f->glGenTextures(1, &new_texture_id);
        f->glBindTexture(GL_TEXTURE_2D, new_texture_id);
        f->glTexImage2D(GL_TEXTURE_2D,
                        0,
                        GL_RGBA,
                        current_image.width(),
                        current_image.height(),
                        0,
                        GL_BGRA,
                        GL_UNSIGNED_BYTE,
                        0);


        /**
        *Min, mag filters
        */
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);





        /**
         *Create pbo and load pixel data into it
         */
        GLuint pbo;
        f->glGenBuffers(1, &pbo);
        f->glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
        f->glBufferData(GL_PIXEL_UNPACK_BUFFER, current_image.byteCount(), 0, GL_STREAM_DRAW);
        f->glBindTexture(GL_TEXTURE_2D, new_texture_id);





        const int line_height = 128;
        for (int i = 0; i < current_image.height() / line_height; i++)
        {




            /**
            *Update device buffer with new data
            */
            f->glBufferSubData(GL_PIXEL_UNPACK_BUFFER,
                               i * line_height * current_image.bytesPerLine(),
                               current_image.bytesPerLine() * line_height,
                               current_image.scanLine(i * line_height));



            /**
            *Update texture with new data in buffer
            */
            f->glTexSubImage2D(GL_TEXTURE_2D,
                               0,
                               0, i * line_height,
                               current_image.width(), line_height,
                               GL_BGRA, GL_UNSIGNED_BYTE,
                               BUFFER_OFFSET(current_image.bytesPerLine() * line_height * i));




            /**
             *Force gpu sync with this thread
             */
            aae::glForceSync(sync_obj, 1e9);




        }




        /**
        *Unbind and delete pbo
        */
        f->glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
        f->glDeleteBuffers(1, &pbo);



        /**
         *Force gpu sync with this thread
         */
        aae::glForceSync(sync_obj, 1e9);



        /**
        *Unbind and add texture to texture library
        */
        f->glBindTexture(GL_TEXTURE_2D, 0);
        m_textures.insert(image_key, new_texture_id);



    }






}




