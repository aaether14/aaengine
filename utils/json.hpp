#ifndef JSON_H
#define JSON_H




#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>



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



    /**
     * @brief SaveJsonToFile will save the provided json to a file
     * @param file_name is the name of the file where the json will be saved
     * @param json_doc is the json document that will be saved to the file
     */
    static void SaveJsonToFile(QString file_name, QJsonDocument json_doc);




};

#endif // JSON_H
