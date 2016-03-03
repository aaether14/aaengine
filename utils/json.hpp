#ifndef JSON_H
#define JSON_H




#include <QJsonDocument>
#include <QFile>



/**
 * @brief The Json class will provide basic json loading functionality
 */
class Json
{


public:


    /**
     * @brief Json is a basic constructor
     */
    Json();



    /**
     * @brief GetJsonFromFile will read the contents of a file and parse it as a json document
     * @param file_name is the filename of the file to be read
     * @return will return the parsed QJsonDocument
     */
    static QJsonDocument GetJsonFromFile(QString file_name);




};

#endif // JSON_H
