#include <fbx_manager/mesh/mesh.hpp>







void Mesh::LoadMaterials(FbxScene *scene, QString fbx_file_name)
{





    for (int i = 0; i < scene->GetMaterialCount(); i++)
    {


        /**
        *If material pointer is null, then continue
        */


        if (!scene->GetMaterial(i))
            continue;


        /**
        If material has already been loaded in the library, continue
        */


        if (materials.contains(scene->GetMaterial(i)->GetName()))
            continue;



        /**
         *Get a pointer to the current material
         */

        FbxSurfaceMaterial * material = scene->GetMaterial(i);


        /**
         * Get the diffuse property of the material
         */

        FbxProperty diffuse_property = material->FindProperty(FbxSurfaceMaterial::sDiffuse);


        Material new_mat;
        new_mat.diffuse_color = Material::FbxPropertyToVector3(diffuse_property);



        if(!diffuse_property.GetSrcObjectCount<FbxFileTexture>() > 0)
            continue;



        FbxFileTexture * texture = diffuse_property.GetSrcObject<FbxFileTexture>();
        if (!texture)
            continue;


        QString texture_index = ComputeTextureFilename(texture->GetFileName(), fbx_file_name);




        if (!QFileInfo(texture_index).exists())
        {
            qDebug() << "Could not find" << texture->GetFileName() <<"!";
            continue;
        }




        /**
        *If the texture is not in the library, add it
        */
        if (!textures.contains(texture_index))
            textures[texture_index] = new QOpenGLTexture(QImage(texture_index).mirrored());




        new_mat.difuse_texture_name = texture_index;
        new_mat.use_diffuse_texture = true;






        materials[material->GetName()] = new_mat;


    }







}

