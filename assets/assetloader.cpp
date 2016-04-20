#include <assets/assetloader.hpp>




void AssetLoader::AddLoader(const QString &loader_name,
                            BaseAssetLoader *loader)
{


    loaders[loader_name] = loader;


}




void AssetLoader::LinkExtensionToLoader(const QString &loader_name,
                                        const QString &extension)
{


    extension_to_loader_map[extension] = loader_name;


}






BaseAsset *AssetLoader::AddAsset(const QString &asset_name,
                                 BaseAsset *new_asset)
{


    assets[asset_name] = new_asset;
    return new_asset;


}





AssetLoader::AssetLoader(QObject *parent) : QObject(parent),
    enque_asset_deletion(false)
{




    setObjectName("AssetLoader");
    AddLoader("FbxLoader", new FBXManager());


#ifdef AAE_USING_FBX
    LinkExtensionToLoader("FbxLoader", "fbx");
#endif
    LinkExtensionToLoader("FbxLoader", "aaem");




}





AssetLoader::~AssetLoader()
{



    qDeleteAll(loaders);
    qDeleteAll(assets);



    assets.clear();
    loaders.clear();



}





void AssetLoader::AddToLoadingStack(const QString &file_name,
                                    const QString &asset_name)
{


    loading_stack.push(QPair<QString, QString>(file_name, asset_name));


}






void AssetLoader::LoadStack()
{





    if (enque_asset_deletion)
    {

        qDeleteAll(assets);
        assets.clear();


        enque_asset_deletion = false;

    }







    while (!loading_stack.isEmpty())
    {


        QPair<QString, QString> new_asset = loading_stack.pop();




        try
        {


            LoadStackInstance(new_asset);


        }


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
     *@brief suffix is the suffix of the file we are trying to load, it is
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
    QString loader_name = extension_to_loader_map[suffix];



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


    BaseAssetLoader * loader = loaders[loader_name];
    loader->Load(instance.first,
                 AddAsset(instance.second, loader->CreateAsset()));





}




BaseAsset *AssetLoader::GetAsset(const QString &asset_name)
{

    return assets[asset_name];

}




bool AssetLoader::HasAsset(const QString &asset_name)
{


    return assets.contains(asset_name);


}




BaseAssetLoader *AssetLoader::GetLoader(const QString &extension)
{


    return loaders[extension_to_loader_map[extension]];


}




bool AssetLoader::HasLoader(const QString &extension)
{


    return loaders.contains(extension_to_loader_map[extension]);


}




void AssetLoader::UnloadAssets()
{


    enque_asset_deletion = true;


}




bool AssetLoader::SanityCheck()
{


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

    AddToLoadingStack(file_name, asset_name);

}




void AssetLoader::logAssetInfo()
{


    qDebug() << assets;


}




