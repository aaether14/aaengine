#ifndef ASSETLOADER_H
#define ASSETLOADER_H




#include <QObject>
#include <QDebug>
#include <QHash>
#include <QStack>
#include <QFileInfo>
#include <assets/baseassetloader.hpp>
#include <fbx_manager/fbxmanager.hpp>



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
     * @param extension is the extension the new loader can load
     * @param loader is the pointer in memory to the newly created loader
     */
    void AddLoader(QString loader_name,
                   QString extension,
                   BaseAssetLoader * loader);


    /**
     * @brief AddAsset gets the new_asset, loads it and adds it to the library
     * @param asset_name - the name of the asset
     * @param new_asset - the asset to be added to the asset library
     * @return returns the loaded asset
     */
    BaseAsset *AddAsset(QString asset_name, BaseAsset * new_asset);




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
    void AddToLoadingStack(QString file_name, QString asset_name);


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
    virtual void LoadStackInstance(QPair<QString, QString> instance);


    /**
     * @brief GetAsset returns the adress of the requested asset
     * @param asset_name is the name of the requested asset
     * @return
     */
    virtual BaseAsset *GetAsset(QString asset_name);


    /**
     * @brief HasAsset will check if a certain asset is in the library
     * @param asset_name is the name of the asset to be checked
     * @return
     */
    virtual bool HasAsset(QString asset_name);


    /**
     * @brief GetLoader will return the adress of loader requested by extension,
     * it is better that you check such an loader exists using HasLoader
     * @param extension is the extension you are requesting a loader for
     * @return
     */
    virtual BaseAssetLoader *GetLoader(QString extension);


    /**
     * @brief HasLoader will check if there is any loader for the provided extension
     * @param extension is the extension you are requesting a loader for
     * @return
     */
    virtual bool HasLoader(QString extension);


    /**
     * @brief UnloadAssets will set the enque_asset_deletion to true
     */
    virtual void UnloadAssets();



    Q_INVOKABLE void loadAsset(QString file_name, QString asset_name);




signals:



public slots:



};

#endif // ASSETLOADER_H
