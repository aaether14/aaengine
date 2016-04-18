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
    /**
     * @brief fbx_file_name is the name of the fbx file
     */
    QString fbx_file_name;




public:


    /**
    * @brief MaterialLoader is a basic constructor
    */
    MaterialLoader(QHash<QString, Material> & r_materials,
                   FbxScene * r_scene,
                   QString fbx_file_name);




    /**
     * @brief Load will load the textures indicated by the fbx file
     */
    void Load();


};

#endif // MATERIALLOADER_H
