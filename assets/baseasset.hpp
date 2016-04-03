#ifndef BASEASSET_H
#define BASEASSET_H



/**
 *@brief The BaseAsset class is an interface for the assets to be added in the
 *asset library
 */
class BaseAsset
{



public:

    /**
     * @brief BaseAsset - basic constructor
     */
    BaseAsset();
    /**
     * @brief ~BaseAsset - basic virtual destructor
     */
    virtual ~BaseAsset() {}


    /**
     * @brief hasData should return true if the asset has any data
     * @return true if the asset has any data
     */
    virtual bool hasData() = 0;


    /**
     * @brief isLoaded should return true if the asset has been successfully loaded
     * @return true if the asset has been successfully loaded
     */
    virtual bool isLoaded() = 0;



};

#endif // BASEASSET_H
