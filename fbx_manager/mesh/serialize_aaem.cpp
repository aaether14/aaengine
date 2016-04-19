#include <fbx_manager/mesh/mesh.hpp>





void Mesh::SerializeAAEM(const QString &file_name)
{





    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not write mesh information to " << file_name << "!";
        return;
    }




    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_5);


    /**
    *First tell what kind of geometry we're dealing with
    */
    out << is_using_normals << is_using_uvs << is_using_tangents;


    /**
    *Save the geometry
    */


    out << d_master_vertices << d_master_indices;


    if (is_using_normals)
        out << d_master_normals;
    if (is_using_uvs)
        out << d_master_uvs;
    if (is_using_tangents)
        out << d_master_tangents;



    out << m_materials << m_mesh_entries;



    file.close();



}






bool Mesh::DeserializeAAEM(const QString &file_name)
{



    /**
     * Clear cache before loading new data
     */



    ClearGeometryData();



    m_mesh_entries.clear();
    m_materials.clear();




    if (QFileInfo(file_name).suffix() != "aaem")
    {
        qDebug() << file_name << "is not the right type of file! (.aaem)";
        return false;
    }




    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not read mesh information from " << file_name << "!";
        return false;
    }



    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_5);



    /**
    *First tell what kind of geometry we're dealing with
    */
    in >> is_using_normals >> is_using_uvs >> is_using_tangents;



    in >> d_master_vertices >> d_master_indices;



    if (is_using_normals)
        in >> d_master_normals;
    if (is_using_uvs)
        in >> d_master_uvs;
    if (is_using_tangents)
        in >> d_master_tangents;



    in >> m_materials >> m_mesh_entries;



    file.close();



}









