#ifndef BASETHREADEDLOADER_H
#define BASETHREADEDLOADER_H




/**
 * @brief The BaseThreadedLoader class is an interface for threaded loaders
 */
class BaseThreadedLoader
{
public:


    /**
     * @brief BaseThreadedLoader is a nothing constructor
     */
    BaseThreadedLoader();


    /**
     * @brief ~BaseThreadedLoader is a nothing destructor
     */
    virtual ~BaseThreadedLoader();


    /**
     * @brief Load will tell the engine how to load certain assets
     */
    virtual void Load() = 0;




};

#endif // BASETHREADEDLOADER_H
