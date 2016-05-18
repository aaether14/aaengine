#include <core/globalsettings.hpp>




QSharedPointer<GlobalSettings> GlobalSettings::m_instance;





GlobalSettings *GlobalSettings::Instance()
{


    /**
    *If no instance exists, create one
    */
    if (m_instance.isNull())
        m_instance.reset(new GlobalSettings);


    /**
    *Return instance
    */
    return m_instance.data();


}




void GlobalSettings::Load(const QString &path)
{


    /**
    *Read config.json to read global settings
    */
    m_config = aae::json::GetJsonFromFile(path).toVariant().toMap();


}




void GlobalSettings::Save(const QString &path)
{

    /**
     *Save m_config to config.json
     */
    aae::json::SaveJsonToFile(path, QJsonDocument(QJsonObject::fromVariantMap(m_config)));


}








