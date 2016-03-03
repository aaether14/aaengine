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
    @brief ~FBXManager will release the fbx sdk when no longer needed
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
     */
    void Load(QString file_name, BaseAsset * asset);


    /**
     * @brief CreateAsset will create a MeshAsset in the heap
     * @return returns a pointer to the newly created MeshAsset
     */
    BaseAsset *CreateAsset();





};

#endif // FBXMANAGER_H
