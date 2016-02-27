#ifndef BASEASSET_H
#define BASEASSET_H


class BaseAsset
{



public:


    BaseAsset();
    virtual ~BaseAsset() {}


    virtual bool isLoaded() = 0;


};

#endif // BASEASSET_H
