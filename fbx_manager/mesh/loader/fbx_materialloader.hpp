#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H




#include <fbx_manager/material/fbx_material.hpp>
#include <assets/basethreadedloader.hpp>



/**
 *@brief The MaterialLoader class will handle material loading in a separate
 *thread
 */
class MaterialLoader : public BaseThreadedLoader
{



    /**
     * @brief materials is the hash where materials are stored
     */
    QHash<QString, Material> & m_materials;
    /**
     * @brief scene is the scene of the fbx file
     */
    FbxScene * m_scene;



public:


    /**
    * @brief MaterialLoader is a basic constructor
    */
    MaterialLoader(QHash<QString, Material> & r_materials,
                   FbxScene * r_scene);




    /**
     * @brief Load will load the textures indicated by the fbx file
     */
    void Load();


};

#endif // MATERIALLOADER_H
