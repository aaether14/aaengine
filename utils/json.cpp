#include <utils/json.hpp>



Json::Json()
{


}



QJsonDocument Json::GetJsonFromFile(QString file_name)
{



    QString file_content;
    QFile file(file_name);




    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open: " << file_name << " to load the json document!";
        return QJsonDocument();
    }



    file_content = file.readAll();
    file.close();


    return QJsonDocument::fromJson(file_content.toUtf8());



}




void Json::SaveJsonToFile(QString file_name, QJsonDocument json_doc)
{



    QFile file(file_name);



    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open: " << file_name << " to save the json document!";
        return;
    }


    file.write(json_doc.toJson());
    file.close();



}



