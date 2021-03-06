#ifndef JSON_H
#define JSON_H




#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>




namespace aae
{



namespace json
{



    /**
     * @brief GetJsonFromFile will read the contents of a file and parse it as a json document
     * @param file_name is the filename of the file to be read
     * @return will return the parsed QJsonDocument
     */
    QJsonDocument GetJsonFromFile(const QString &file_name);



    /**
     * @brief SaveJsonToFile will save the provided json to a file
     * @param file_name is the name of the file where the json will be saved
     * @param json_doc is the json document that will be saved to the file
     */
     void SaveJsonToFile(const QString &file_name,
                               const QJsonDocument &json_doc);




}



}

#endif // JSON_H
