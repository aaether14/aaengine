#include <fbx_manager/mesh/mesh.hpp>







void Mesh::LoadMaterials(FbxScene *scene, QString fbx_file_name)
{



    materials.clear();



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
         *Create a new material and add properties to it
         */


        Material new_mat;




        new_mat.AddDiffuseProperty(material->FindProperty(FbxSurfaceMaterial::sDiffuse),
                                   textures,
                                   fbx_file_name);




        new_mat.AddNormalProperty(material->FindProperty(FbxSurfaceMaterial::sNormalMap),
                                  textures,
                                  fbx_file_name);





        materials[material->GetName()] = new_mat;


    }







}

