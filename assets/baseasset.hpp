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
     * @brief isLoaded is a pure virtual function that will be needed
     *  to provide in order to instantiate any BaseAsset
     * @return should return true if the asset has been successfully loaded
     */
    virtual bool isLoaded() = 0;


};

#endif // BASEASSET_H
