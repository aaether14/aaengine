#include <utils/json.hpp>



Json::Json()
{


}



QJsonDocument Json::GetJsonFromFile(QString file_name)
{



    QString file_content;
    QFile file;



    file.setFileName(file_name);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    file_content = file.readAll();
    file.close();


    return QJsonDocument::fromJson(file_content.toUtf8());



}
