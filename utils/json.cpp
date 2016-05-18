#include <utils/json.hpp>




namespace aae
{




namespace json
{




QJsonDocument GetJsonFromFile(const QString &file_name)
{


    /**
     *File content container
     */
    QString file_content;
    QFile file(file_name);



    /**
    *Open file for reading
    */
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open: " << file_name << " to load the json document!";
        return QJsonDocument();
    }


    /**
    *Read file content then close it
    */
    file_content = file.readAll();
    file.close();


    /**
    *Return serialized json
    */
    return QJsonDocument::fromJson(file_content.toUtf8());



}




void SaveJsonToFile(const QString &file_name,
                    const QJsonDocument &json_doc)
{



    QFile file(file_name);



    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open: " << file_name << " to save the json document!";
        return;
    }


    file.write(json_doc.toJson());
    file.close();



}






}




}
