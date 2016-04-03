#include <fbx_manager/mesh/materialloader.hpp>






MaterialLoader::MaterialLoader(QHash<QString, Material> &materials,
                               QHash<QString, QImage> &images,
                               FbxScene *scene,
                               QString fbx_file_name) :


    materials(materials),
    images(images),
    scene(scene),
    fbx_file_name(fbx_file_name)




{





}

void MaterialLoader::Load()
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
                                   images,
                                   fbx_file_name);




        new_mat.AddNormalProperty(material->FindProperty(FbxSurfaceMaterial::sNormalMap),
                                  images,
                                  fbx_file_name);





        materials[material->GetName()] = new_mat;



    }




    emit HasLoadedMaterials();




}


