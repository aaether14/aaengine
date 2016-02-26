#ifndef BASEASSETLOADER_H
#define BASEASSETLOADER_H




#include <assets/baseasset.hpp>
#include <QString>




class BaseAssetLoader
{



public:


    BaseAssetLoader();


    virtual void Load(QString file_name, BaseAsset * asset) = 0;



};



#endif // BASEASSETLOADER_H
