#include <fbx_manager/mesh/mesh.hpp>
#include <dialogs/console/logger.hpp>





#define AAEM_SERIALIZER_VERSION 0xffff02
#define AAEM_DESERIALIZER_VERSION 0xffff02






void Mesh::SerializeAAEM(const QString &file_name)
{




    /**
     *Open the file to serialize to
     */
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly))
    {
        Logger::Instance()->safeLog("Could not write mesh information to " + file_name + " !");
        return;
    }



    /**
     *Provide with qt serializer version
     */
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_6);



    /**
     *Provide with aaem serializer version
     */
    qint32 aaem_version = AAEM_SERIALIZER_VERSION;
    out << aaem_version;




    /**
    *First tell what kind of geometry we're dealing with
    */
    out << is_using_normals << is_using_uvs << is_using_tangents;


    /**
    *Save the geometry
    */
    out << d_master_vertices << d_master_indices;


    /**
    *Save additional geometry layers
    */
    if (is_using_normals)
        out << d_master_normals;
    if (is_using_uvs)
        out << d_master_uvs;
    if (is_using_tangents)
        out << d_master_tangents;


    /**
    *Save material data and mesh entries
    */
    out << m_materials << m_mesh_entries;


    /**
    *Pack texture data
    */
    out << d_images;



    /**
    *Now that we're done, close the file
    */
    file.close();



}






bool Mesh::DeserializeAAEM(const QString &file_name)
{



    /**
     * Clear cache before loading new data
     */
    ClearGeometryData();



    /**
    *Clear and entry or material information before loading new one
    */
    m_mesh_entries.clear();
    m_materials.clear();




    /**
    *Check if the file has right extension
    */
    if (QFileInfo(file_name).suffix() != "aaem")
    {
        Logger::Instance()->safeLog(file_name + " is not the right type of file! (.aaem)");
        return false;
    }



    /**
     *Open the file to be deserialized
     */
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly))
    {
        Logger::Instance()->safeLog("Could not read mesh information from " + file_name + " !");
        return false;
    }



    /**
     *Set qt deserializer version
     */
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_6);



    /**
     *Get aaem serializer version
     */
    qint32 aaem_version;
    in >> aaem_version;



    /**
    *Check if the file has a compatible serializer version
    */
    if (aaem_version != AAEM_DESERIALIZER_VERSION)
    {

        Logger::Instance()->safeLog(file_name + " has an unsupported file version!");
        /**
        *Close the file and return
        */
        file.close();
        return false;

    }



    /**
    *First tell what kind of geometry we're dealing with
    */
    in >> is_using_normals >> is_using_uvs >> is_using_tangents;


    /**
    *Get base geometry
    */
    in >> d_master_vertices >> d_master_indices;


    /**
    *Get additional geometry layers
    */
    if (is_using_normals)
        in >> d_master_normals;
    if (is_using_uvs)
        in >> d_master_uvs;
    if (is_using_tangents)
        in >> d_master_tangents;


    /**
    *Get materials, mesh entries and load images used by materials
    */
    in >> m_materials >> m_mesh_entries;
    in >> d_images;


    /**
    *Now that we're done deserializing, close the file
    */
    file.close();



    /**
    *Everything went well, signal successful load
    */
    return true;




}









