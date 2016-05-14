#ifndef FBXMATERIAL_H
#define FBXMATERIAL_H



#include <aae_defines.hpp>



#include <material/material.hpp>
#include <fbx_manager/mesh_util.hpp>



#ifdef AAE_USING_FBX
#include <fbxsdk.h>
#endif






/**
 * @brief The FbxMaterial class holds material data
 */
class FbxMaterial : public Material
{


public:


#ifdef AAE_USING_FBX
    /**
     * @brief AddProperty will add a certain property to the material
     * @param property is the property to be added
     * @param factor_property is the factor property to be added (i.e intensity)
     */
    void AddProperty(const FbxProperty &property,
                     const FbxProperty &factor_property);
#endif



};






#endif // FBXMATERIAL_H
