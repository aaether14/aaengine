#include <assets/assetloader.hpp>





void AssetLoader::AddLoader(const QString &loader_name,
                            BaseAssetLoader *loader)
{


    /**
    *Add the provided loader to the hash
    */
    loaders.insert(loader_name, loader);


}




void AssetLoader::LinkExtensionToLoader(const QString &loader_name,
                                        const QString &extension)
{


    /**
    *Link a certain extention to a loader that could load those kind of files
    */
    extension_to_loader_map.insert(extension, loader_name);


}






BaseAsset *AssetLoader::AddAsset(const QString &asset_name,
                                 BaseAsset *new_asset)
{


    /**
    *Add the asset to the library and also return a reference of it
    */
    assets.insert(asset_name, new_asset);
    return new_asset;


}





AssetLoader::AssetLoader(QObject *parent) : QObject(parent),
    enque_asset_deletion(false)
{



    /**
     *Set the name of the QObject
     */
    setObjectName("AssetLoader");
    /**
     *Add the loaders that will be used to load certain assets to the library
     */
    AddLoader("FbxLoader", new FBXManager());





#ifdef AAE_USING_FBX
/**
*Link certain extensions to the matching loaders
*/
    LinkExtensionToLoader("FbxLoader", "fbx");
#endif
    LinkExtensionToLoader("FbxLoader", "aaem");




}





AssetLoader::~AssetLoader()
{



    /**
     *Delete the loaders and the assets
     */
    qDeleteAll(loaders);
    qDeleteAll(assets);



    /**
    *Then clear the hash
    */
    assets.clear();
    loaders.clear();



}





void AssetLoader::AddToLoadingStack(const QString &file_name,
                                    const QString &asset_name)
{

    /**
    *Issue a command to load a certain asset when the opengl context is made current
    */
    loading_stack.push(QPair<QString, QString>(file_name, asset_name));


}






void AssetLoader::LoadStack()
{




    /**
    *If the asset deletion has been requested, do so now that opengl context is current
    */
    if (enque_asset_deletion)
    {

        qDeleteAll(assets);
        assets.clear();


        enque_asset_deletion = false;

    }






    /**
    *While there are loading commands left...
    */
    while (!loading_stack.isEmpty())
    {


        /**
         *Get a loading command
         */
        QPair<QString, QString> new_asset = loading_stack.pop();




        try
        {

            /**
             *Try to load requested asset
             */
            LoadStackInstance(new_asset);


        }

        /**
        *And catch errors to output their message
        */
        catch(aae::AError &error)
        {


            qDebug() << "An error occured while trying to load an Asset!";
            qDebug() << error.what();



        }





    }





}



void AssetLoader::LoadStackInstance(const QPair<QString, QString> &instance)
{




    /**
    First check whether of not the asset is already in the library
    */
    if (assets.contains(instance.second))
    {

        QString msg = instance.second + " is already in the library!";
        throw aae::AError(msg);

    }





    /**
    Also check if the file we are trying to load even exists
    */
    if (!QFileInfo(instance.first).exists())
    {

        QString msg = instance.first + " does not exist!";
        throw aae::AError(msg);

    }



    /**
     *Get the suffix of the file we are trying to load, it is
     *useful because we will direct the file towards coresponding loader
     */
    QString suffix = QFileInfo(instance.first).suffix();




    /**
    Check whether of not there is any loader that can load this extension
    */
    if (!extension_to_loader_map.contains(suffix))
    {
        QString msg = "No " + suffix + " loader available!";
        throw aae::AError(msg);
    }



    /**
     * @brief loader_name is the name of the loader we are trying to use in order to load the new asset
     */
    QString loader_name = extension_to_loader_map.value(suffix);



    /**
    Check if for some reason the desired load is not in the loader library
    */
    if (!loaders.contains(loader_name))
    {
        QString msg = loader_name + " was not found in the expected location!";
        throw aae::AError(msg);
    }





    /**
     *If everything went well go ahead and load the asset using the right
     *loader
     */
    BaseAssetLoader * loader = loaders.value(loader_name);
    loader->Load(instance.first,
                 AddAsset(instance.second, loader->CreateAsset()));





}




BaseAsset *AssetLoader::GetAsset(const QString &asset_name)
{

    /**
    *Get a certain assrt from the library
    */
    return assets.value(asset_name);

}




bool AssetLoader::HasAsset(const QString &asset_name)
{


    /**
    *Tell if a certain asset exists in the library
    */
    return assets.contains(asset_name);


}




BaseAssetLoader *AssetLoader::GetLoader(const QString &extension)
{


    /**
    *Get a certain loader from the library
    */
    return loaders.value(extension_to_loader_map.value(extension));


}




bool AssetLoader::HasLoader(const QString &extension)
{

    /**
    *Tell if a certain loader exists in the library
    */
    return loaders.contains(extension_to_loader_map.value(extension));


}




void AssetLoader::UnloadAssets()
{


    /**
    *Enque a deletion of the assets in the library
    */
    enque_asset_deletion = true;


}




bool AssetLoader::SanityCheck()
{


    /**
    *Check if all assets are loaded correctly
    */
    foreach(auto it, assets)
    {
        if (!it->isLoaded())
            return false;
    }


    return true;


}





void AssetLoader::loadAsset(const QString &file_name,
                            const QString &asset_name)
{

    /**
     *Issue a loading command to load a certain asset
     */
    AddToLoadingStack(file_name, asset_name);

}




void AssetLoader::logAssetInfo()
{

    /**
    *Log the assets in the library
    */
    qDebug() << assets;


}




