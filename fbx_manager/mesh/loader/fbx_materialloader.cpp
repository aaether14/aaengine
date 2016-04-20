#include <fbx_manager/mesh/loader/fbx_materialloader.hpp>





#ifdef AAE_USING_FBX
MaterialLoader::MaterialLoader(QHash<QString, Material> &r_materials,
                               FbxScene *r_scene) :


    m_materials(r_materials),
    m_scene(r_scene)
{


    /**
    *Pass the references to required data
    */


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
        new_mat.AddProperty(material->FindProperty(FbxSurfaceMaterial::sDiffuse));
        new_mat.AddProperty(material->FindProperty(FbxSurfaceMaterial::sNormalMap));



        m_materials[material->GetName()] = new_mat;



    }




}
#endif

