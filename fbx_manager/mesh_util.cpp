#include <fbx_manager/mesh_util.hpp>




namespace aae
{




mesh_util::mesh_util()
{

}





QString mesh_util::ComputeTextureFilename(QString texture_name, QString fbx_file_name)
{



    QString texture_file_name;


    /**
    *first put the name of the texture in a standard form, then get just from
    *it
    */


    texture_name.replace("\\", "/");
    texture_name = texture_name.mid(texture_name.lastIndexOf("/") + 1, texture_name.length());




    QString directory;



    /**
    *get the directory for the texture
    */


    if (QString(fbx_file_name).lastIndexOf("/") > 0)
    {
        directory = QString(fbx_file_name).mid(0, QString(fbx_file_name).lastIndexOf("/"));
    }




    if (directory.length() > 0)
    {
        texture_file_name = directory + "/" + texture_name;
    }




    /**
    Check if the texture exists in the folder of the fbx model. If so, return
    the computed texture name, otherwise try in the .fbm folder in the same
    location
    */
    if (QFileInfo(texture_file_name).exists())
    {
        return texture_file_name;
    }
    else
    {


        texture_file_name = directory + "/" + QFileInfo(fbx_file_name).baseName() + ".fbm/" + texture_name;



        if (QFileInfo(texture_file_name).exists())
        {
            return texture_file_name;
        }
        else
        {
            return QString();
        }



    }



}




#ifdef AAE_USING_FBX
QVector3D mesh_util::QVector3DFromFbxVector3D(FbxDouble3 vec)
{


    return QVector3D(vec.mData[0], vec.mData[1], vec.mData[2]);


}
#endif





}
