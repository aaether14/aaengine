#include <fbx_manager/mesh_util.hpp>




namespace aae
{



namespace mesh_util
{



QString ComputeTextureFilename(QString texture_name, QString fbx_file_name)
{



    /**
     *Here we will compute an eventual texture name required by the mesh
     */
    QString texture_file_name;


    /**
    *First put the name of the texture in a standard form
    */
    texture_name.replace("\\", "/");
    texture_name = texture_name.mid(texture_name.lastIndexOf("/") + 1, texture_name.length());


    /**
     *We need the directory of the file
     */
    QString directory;



    /**
    *Get the directory for the texture
    */
    if (QString(fbx_file_name).lastIndexOf("/") > 0)
    {
        directory = QString(fbx_file_name).mid(0, QString(fbx_file_name).lastIndexOf("/"));
    }



    /**
    *Compute the texture file name with repsect to the directory of the file
    */
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

        /**
        *Compute fbx texture name in the case it lies inside a .fbm folder
        */
        texture_file_name = directory + "/" + QFileInfo(fbx_file_name).baseName() + ".fbm/" + texture_name;


        /**
        *If the texture exists return it's path, if not return empty string
        */
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
QVector3D QVector3DFromFbxVector3D(FbxDouble3 vec)
{


    return QVector3D(vec.mData[0], vec.mData[1], vec.mData[2]);


}
#endif





}




}
