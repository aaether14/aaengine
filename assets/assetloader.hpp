#ifndef ASSETLOADER_H
#define ASSETLOADER_H




#include <QObject>
#include <QDebug>
#include <QHash>
#include <QStack>
#include <QFileInfo>
#include <assets/baseassetloader.hpp>
#include <fbx_manager/fbxmanager.hpp>





class AssetLoader : public QObject
{



    Q_OBJECT



    QHash<QString, BaseAssetLoader*> loaders;
    QHash<QString, QString> extension_to_loader_map;



    QStack<QPair<QString,QString> > loading_stack;
    QHash<QString, BaseAsset*> assets;



    void AddLoader(QString loader_name, QString extension, BaseAssetLoader * loader);



    BaseAsset *AddAsset(QString asset_name, BaseAsset * new_asset);




public:



   explicit AssetLoader(QObject *parent = 0);
   ~AssetLoader();



    void AddToLoadingStack(QString file_name, QString asset_name);



    virtual void LoadStack();



    virtual BaseAsset *GetAsset(QString asset_name);



    Q_INVOKABLE void loadAsset(QString file_name, QString asset_name);




signals:



public slots:



};

#endif // ASSETLOADER_H
