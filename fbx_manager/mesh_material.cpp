#include <fbx_manager/mesh.hpp>







void Mesh::LoadMaterials(FbxScene *scene, QString fbx_file_name)
{





    for (int i = 0; i < scene->GetMaterialCount(); i++)
    {


        FbxSurfaceMaterial * material = scene->GetMaterial(i);
        if (material)
        {


            if (!materials.contains(material->GetName()))
            {


                FbxProperty diffuse_prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);



                Material new_mat;
                new_mat.diffuse_color = Material::FbxPropertyToVector3(diffuse_prop);



                if(diffuse_prop.GetSrcObjectCount<FbxFileTexture>() > 0)
                {



                    FbxFileTexture * texture = diffuse_prop.GetSrcObject<FbxFileTexture>();
                    if (texture)
                    {



                        QString texture_index = ComputeTextureFilename(texture->GetFileName(), fbx_file_name);
                        if (QFileInfo(texture_index).exists())
                        {
                            if (!textures.contains(texture_index))
                            {
                                textures[texture_index] = new QOpenGLTexture(QImage(texture_index).mirrored());
                            }
                            new_mat.difuse_texture_name = texture_index;
                            new_mat.use_diffuse_texture = true;
                        }
                        else
                            qDebug() << "Could not find" << texture->GetFileName() <<"!";





                    }





                }


                materials[material->GetName()] = new_mat;


            }

        }


    }




}

