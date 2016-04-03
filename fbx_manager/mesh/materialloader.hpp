#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H



#include <QObject>
#include <fbx_manager/material/material.hpp>



/**
 *@brief The MaterialLoader class will handle material loading in a separate
 *thread
 */
class MaterialLoader : public QObject
{


    Q_OBJECT


    /**
     * @brief materials is the hash where materials are stored
     */
    QHash<QString, Material> & materials;
    /**
     * @brief images is the hash where images are stored
     */
    QHash<QString, QImage> & images;
    /**
     * @brief scene is the scene of the fbx file
     */
    FbxScene * scene;
    /**
     * @brief fbx_file_name is the name of the fbx file
     */
    QString fbx_file_name;




public:


    /**
    * @brief MaterialLoader is a basic constructor
    */
    MaterialLoader(QHash<QString, Material> & materials,
                   QHash<QString, QImage> & images,
                   FbxScene * scene,
                   QString fbx_file_name);


signals:

    /**
     *@brief HasLoadedMaterials will be emitted when the loaded has done it's
     *job
     */
    void HasLoadedMaterials();



public slots:


    /**
     * @brief Load will load the textures indicated by the fbx file
     */
    void Load();


};

#endif // MATERIALLOADER_H
