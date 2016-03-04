#include <assets/assetloader.hpp>




void AssetLoader::AddLoader(QString loader_name, QString extension, BaseAssetLoader *loader)
{


    loaders[loader_name] = loader;
    extension_to_loader_map[extension] = loader_name;


}




BaseAsset *AssetLoader::AddAsset(QString asset_name, BaseAsset *new_asset)
{


    assets[asset_name] = new_asset;
    return new_asset;


}





AssetLoader::AssetLoader(QObject *parent) : QObject(parent),
    enque_asset_deletion(false)
{


    setObjectName("AssetLoader");
    AddLoader("FbxLoader", "fbx", new FBXManager());



}





AssetLoader::~AssetLoader()
{


    qDeleteAll(loaders);
    qDeleteAll(assets);

    assets.clear();
    loaders.clear();

}





void AssetLoader::AddToLoadingStack(QString file_name, QString asset_name)
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



        if (assets.contains(new_asset.second))
        {

            qDebug() << "AssetLoader: " << new_asset.second << " already in the asset library!";
            continue;

        }



        if (!QFileInfo(new_asset.first).exists())
        {
            qDebug() << "AssetLoader: " << new_asset.first << " does not exist!";
            continue;
        }


        QString suffix = QFileInfo(new_asset.first).suffix();



        if (!extension_to_loader_map.contains(suffix))
        {
            qDebug() << "AssetLoader: No " << suffix << " loader available!";
            continue;
        }


        QString loader_name = extension_to_loader_map[suffix];


        if (!loaders.contains(loader_name))
        {
            qDebug() << "AssetLoader: " << loader_name << " was not found in the expected location!";
        }


        BaseAssetLoader * loader = loaders[loader_name];
        loader->Load(new_asset.first,
                     AddAsset(new_asset.second, loader->CreateAsset()));



    }


}




BaseAsset *AssetLoader::GetAsset(QString asset_name)
{

    return assets[asset_name];

}




bool AssetLoader::HasAsset(QString asset_name)
{


    return assets.contains(asset_name);


}




void AssetLoader::UnloadAssets()
{


    enque_asset_deletion = true;


}





void AssetLoader::loadAsset(QString file_name, QString asset_name)
{

    AddToLoadingStack(file_name, asset_name);

}




