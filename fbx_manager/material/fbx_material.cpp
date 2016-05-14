#include <fbx_manager/material/fbx_material.hpp>








#ifdef AAE_USING_FBX
void FbxMaterial::AddProperty(const FbxProperty &property,
                           const FbxProperty &factor_property)
{




    /**
    *If we are dealing with an invalid properties, abort
    */
    if (!property.IsValid() || !factor_property.IsValid())
        return;




    /**
     *Get the name of the property
     */
    QString property_name = property.GetNameAsCStr();


    /**
    *Based on the property's name, load required stuff
    */
    if (property_name == FbxSurfaceMaterial::sDiffuse)
    {



        /**
         *Get the diffuse color and intensity
         */
        FbxDouble3 diffuse_color = property.Get<FbxDouble3>();
        FbxDouble diffuse_intensity = factor_property.Get<FbxDouble>();



        /**
         *Set diffuse color and intensity
         */
        SetDiffuseColor(aae::mesh_util::QVector3DFromFbxVector3D(diffuse_color));
        SetDiffuseIntensity(diffuse_intensity);




        /**
        *If there are no textures attached to the property, return
        */
        if(!property.GetSrcObjectCount<FbxFileTexture>() > 0)
            return;



        /**
         *Get the texture handler
         */
        FbxFileTexture * texture = property.GetSrcObject<FbxFileTexture>();
        if (!texture)
            return;



        /**
        *Add the diffuse texture name of the material
        */
        AddTexture(diffuse, texture->GetFileName());


    }
    else if (property_name == FbxSurfaceMaterial::sNormalMap)
    {


        /**
        *If there are no textures attached to the property, return
        */
        if(!property.GetSrcObjectCount<FbxFileTexture>() > 0)
            return;


        /**
         *Get the texture handler
         */
        FbxFileTexture * texture = property.GetSrcObject<FbxFileTexture>();
        if (!texture)
            return;


        /**
        *Set normal map texture of the material
        */
        AddTexture(normal, texture->GetFileName());


    }
    else if (property_name == FbxSurfaceMaterial::sSpecular)
    {


        /**
         *Get the specular color and intensity
         */
        FbxDouble3 specular_color = property.Get<FbxDouble3>();
        FbxDouble specular_intensity = factor_property.Get<FbxDouble>();



        /**
        *Set the specular color and intensity
        */
        SetSpecularColor(aae::mesh_util::QVector3DFromFbxVector3D(specular_color));
        SetSpecularIntensity(specular_intensity);



    }
    else if (property_name == FbxSurfaceMaterial::sShininess)
    {


        /**
         *Get and set specular hardness
         */
        FbxDouble specular_hardness = property.Get<FbxDouble>();
        SetSpecularHardness(specular_hardness);


    }





}
#endif





