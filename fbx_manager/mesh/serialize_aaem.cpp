#include <fbx_manager/mesh/mesh.hpp>





void Mesh::SerializeAAEM(QString file_name)
{



    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not write mesh information to " << file_name << "!";
        return;
    }



    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_5);


    out << is_using_normals << is_using_uvs << is_using_tangents;


    file.close();



}




