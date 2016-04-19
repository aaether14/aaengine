#ifndef FBXMANAGER_H
#define FBXMANAGER_H




#include <QDebug>
#include <fbxsdk.h>
#include <assets/baseassetloader.hpp>
#include <assets/meshasset.hpp>




/**
 *@brief The FBXManager class derives from the BaseAssetLoader and will handle
 *the loading of fbx models using the fbx sdk
 */
class FBXManager : public BaseAssetLoader
{




    /**
     * @brief manager is the manager of the fbx sdk
     */
    FbxManager * manager;




public:


    /**
     * @brief FBXManager will initialize the fbx sdk
     */
    FBXManager();


    /**
    *~FBXManager will destroy the fbx sdk mananger
    */
    ~FBXManager();


    /**
     * @brief GetManager will return the fbx sdk manager
     * @return
     */
    inline FbxManager * GetManager(){return manager; }

    /**
     * @brief Load will load the fbx model into the provided MeshAsset
     * @param file_name is the name of the fbx file
     * @param asset is the pointer to the asset data will stored into
     * @param load_options is a hash map of options you want the
     * loader to keep account of
     */
    void Load(const QString &file_name,
              BaseAsset * asset,
              const QVariantMap &load_options);


    /**
     * @brief CreateAsset will create a MeshAsset in the heap
     * @return returns a pointer to the newly created MeshAsset
     */
    BaseAsset *CreateAsset();





    /**
     * @brief ImportScene will import the data from the fbx file to the scene
     * @param mesh is the mesh whose scene will be imported
     * @param fbx_file_name is the name of the fbx file
     * @return true on importing successfully
     */
    bool ImportScene(Mesh * mesh,
                     QString fbx_file_name);



    /**
     * @brief ExportScene will export the data from the scene of the mesh to a file
     * @param mesh is the mesh whose scene we will export
     * @param fbx_file_name is the name of the fbx file
     */

    void ExportScene(Mesh * mesh,
                     QString fbx_file_name);






};

#endif // FBXMANAGER_H
