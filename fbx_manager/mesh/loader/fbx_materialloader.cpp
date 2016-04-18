#include <fbx_manager/mesh/loader/fbx_materialloader.hpp>






MaterialLoader::MaterialLoader(QHash<QString, Material> &r_materials,
                               FbxScene *r_scene,
                               QString fbx_file_name) :


    m_materials(r_materials),
    m_scene(r_scene),
    fbx_file_name(fbx_file_name)




{





}

void MaterialLoader::Load()
{



    m_materials.clear();



    for (qint32 i = 0; i < m_scene->GetMaterialCount(); i++)
    {



        /**
        *If material pointer is null, then continue
        */


        if (!m_scene->GetMaterial(i))
            continue;


        /**
        If material has already been loaded in the library, continue
        */


        if (m_materials.contains(m_scene->GetMaterial(i)->GetName()))
            continue;



        /**
         *Get a pointer to the current material
         */

        FbxSurfaceMaterial * material = m_scene->GetMaterial(i);




        /**
         *Create a new material and add properties to it
         */


        Material new_mat;




        new_mat.AddDiffuseProperty(material->FindProperty(FbxSurfaceMaterial::sDiffuse),
                                   fbx_file_name);




        new_mat.AddNormalProperty(material->FindProperty(FbxSurfaceMaterial::sNormalMap),
                                  fbx_file_name);



        m_materials[material->GetName()] = new_mat;



    }




}


