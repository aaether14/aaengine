#ifndef BASEASSETLOADER_H
#define BASEASSETLOADER_H




#include <assets/baseasset.hpp>
#include <QString>
#include <QVariantMap>




/**
 *@brief The BaseAssetLoader class is an interface for AssetLoaders
 */
class BaseAssetLoader
{



public:


    /**
     * @brief BaseAssetLoader - basic constructor
     */
    BaseAssetLoader();
    /**
     * @brief ~BaseAssetLoader - basic destructor
     */
    virtual ~BaseAssetLoader() {}


    /**
     * @brief Load is a pure virtual function that has to be provided in order
     *  to instantiate an AssetLoader, each loader will have
     * a loading routine for the assets it targets
     * @param file_name is the name of the file the loader will try to load
     * @param asset is the asset where the loader will try to load the data into
     * @param load_options is a hash map of options you want the loader to keep
     * account of
     */
    virtual void Load(QString file_name,
                      BaseAsset * asset,
                      QVariantMap load_options = QVariantMap()) = 0;

    /**
     * @brief CreateAsset should create an instance of a class deriving from BaseAsset
     * that can handle the data in the file the
     * loader should load
     * @return
     */
    virtual BaseAsset * CreateAsset() = 0;



};



#endif // BASEASSETLOADER_H
