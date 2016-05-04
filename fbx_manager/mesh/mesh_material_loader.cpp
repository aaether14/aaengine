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




void Mesh::PassTextureDataToOpenGL()
{





    /**
    *Load textures into opengl memory
    */
    foreach(auto current_material, m_materials)
        foreach(auto current_texture, current_material.GetTextures().values())
            if (!m_textures.contains(current_texture))
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
                m_textures.insert(current_texture, new QOpenGLTexture(QImage(texture_index).mirrored()));

            }





}




