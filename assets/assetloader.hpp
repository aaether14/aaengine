#ifndef ASSETLOADER_H
#define ASSETLOADER_H




#include <QObject>
#include <QDebug>
#include <QHash>
#include <QStack>
#include <QFileInfo>
#include <assets/baseassetloader.hpp>
#include <fbx_manager/fbxmanager.hpp>


#include <aae_defines.hpp>
#include <error/aerror.hpp>



/**
 *@brief The AssetLoader class is the instance of the engine responsable for
 *loading of assets, it is also accessable from scripts
 */
class AssetLoader : public QObject
{



    Q_OBJECT


    /**
     * @brief loaders will hold the asset loaders by their name
     */
    QHash<QString, BaseAssetLoader*> loaders;
    /**
     *@brief extension_to_loader_map will tie a certain loader to the extension
     *it is adressed to load
     */
    QHash<QString, QString> extension_to_loader_map;


    /**
     *@brief loading_stack will hold the information of the assets to be loaded
     *untill this opperation is posible (while in opengl context)
     */
    QStack<QPair<QString,QString> > loading_stack;
    /**
     * @brief assets is the asset library
     */
    QHash<QString, BaseAsset*> assets;



    /**
     * @brief AddLoader will add a new loader
     * @param loader_name is the name of the new loader
     * @param loader is the pointer in memory to the newly created loader
     */
    void AddLoader(const QString &loader_name,
                   BaseAssetLoader * loader);



    /**
     * @brief LinkExtensionToLoader will link an extension to a certain loader in the library
     * @param loader_name is the name of the loader to link against
     * @param extension is the extension to link
     */
    void LinkExtensionToLoader(const QString &loader_name,
                               const QString &extension);



    /**
     * @brief AddAsset gets the new_asset, loads it and adds it to the library
     * @param asset_name - the name of the asset
     * @param new_asset - the asset to be added to the asset library
     * @return returns the loaded asset
     */
    BaseAsset *AddAsset(const QString &asset_name,
                        BaseAsset * new_asset);




    /**
     *@brief enque_asset_deletion will be true when assets are about to be
     *deleting when entering the opengl context
     */
    bool enque_asset_deletion;




public:


    /**
     * @brief AssetLoader will add some basic loaders such as fbx loader
     * @param parent
     */
    explicit AssetLoader(QObject *parent = 0);
    /**
     @brief ~AssetLoader will delete the loaders and the assets
     */
    ~AssetLoader();




    /**
     * @brief AddToLoadingStack - see loading_stack
     * @param file_name is the file to be loaded
     * @param asset_name is the alias of the asset to be loaded
     */
    void AddToLoadingStack(const QString &file_name,
                           const QString &asset_name);


    /**
     *@brief LoadStack is the loading routine that has to be called while in
     *opengl context
     */
    virtual void LoadStack();


    /**
     * @brief LoadStackInstance will try to load a single instance from the
     * loading stack
     * @param instance is the instance we will try to load
     */
    virtual void LoadStackInstance(const QPair<QString, QString> &instance);


    /**
     * @brief GetAsset returns the adress of the requested asset
     * @param asset_name is the name of the requested asset
     * @return
     */
    virtual BaseAsset *GetAsset(const QString &asset_name);


    /**
     * @brief HasAsset will check if a certain asset is in the library
     * @param asset_name is the name of the asset to be checked
     * @return
     */
    virtual bool HasAsset(const QString &asset_name);


    /**
     * @brief GetLoader will return the adress of loader requested by extension,
     * it is better that you check such an loader exists using HasLoader
     * @param extension is the extension you are requesting a loader for
     * @return
     */
    virtual BaseAssetLoader *GetLoader(const QString &extension);


    /**
     * @brief HasLoader will check if there is any loader for the provided extension
     * @param extension is the extension you are requesting a loader for
     * @return
     */
    virtual bool HasLoader(const QString &extension);


    /**
     * @brief UnloadAssets will set the enque_asset_deletion to true
     */
    virtual void UnloadAssets();



    /**
     * @brief SanityCheck will be true if all the meshes are loaded successfully
     * @return true if all the meshes are loaded successfully
     */
    virtual bool SanityCheck();



    /**
    *@brief loadAsset will load a certain asset to the library
    *@param file_name is the name of the file to load
    *@param asset_name is the name by which the asset will be identified in the scene
    */
    Q_INVOKABLE void loadAsset(const QString &file_name,
                               const QString &asset_name);



    /**
    *@brief logAssetInfo will log to the console the assets in the library
    */
    Q_INVOKABLE void logAssetInfo();




signals:



public slots:



};

#endif // ASSETLOADER_H
