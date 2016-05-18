#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H




#include <QSharedPointer>
#include <utils/json.hpp>




/**
 *@brief The GlobalSettings class will hold the global settings from config.json
 *in a signleton pattern
 */
class GlobalSettings
{


    /**
     *@brief m_config will hold the information specified in the config.json
     */
    QVariantMap m_config;


    /**
     *This is the instance of the singleton
     */
    static QSharedPointer<GlobalSettings> m_instance;



public:


    /**
    *This is a default constructor
    */
    GlobalSettings() = default;


    /**
     * @brief Instance will return the instance of the singleton
     * @return m_instance
     */
    static GlobalSettings * Instance();


    /**
     * @brief Load will load the settings from config.json
     * @param path is the path to config.json
     */
    void Load(const QString &path);

    /**
     * @brief Save will save m_config to config.json
     * @param path is the path to config.json
     */
    void Save(const QString &path);

    /**
     * @brief Get will get config.json settings object
     * @return m_config
     */
    inline const QVariantMap & Get() const{
        return m_config;
    }


    /**
     * @brief Set will set a certain value in m_config
     * @param key is the key to be set
     * @param value is the value to be set
     */
    inline void Set(const QString &key, const QVariant &value){
        m_config.insert(key, value);
    }



};



#endif // GLOBALSETTINGS_H
