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





AssetLoader::AssetLoader(QObject *parent) : QObject(parent)
{


    setObjectName("AssetLoader");
    AddLoader("FbxLoader", "fbx", new FBXManager());



}





AssetLoader::~AssetLoader()
{

    qDeleteAll(loaders);

}





void AssetLoader::AddToLoadingStack(QString file_name, QString asset_name)
{


    loading_stack.push(QPair<QString, QString>(file_name, asset_name));


}




void AssetLoader::LoadStack()
{


    while (!loading_stack.isEmpty())
    {


        QPair<QString, QString> new_asset = loading_stack.pop();
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





void AssetLoader::loadAsset(QString file_name, QString asset_name)
{

    AddToLoadingStack(file_name, asset_name);

}




