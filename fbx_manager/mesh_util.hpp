#ifndef MESH_UTIL_H
#define MESH_UTIL_H




#include <QString>
#include <QVector3D>
#include <QFileInfo>
#include <fbxsdk.h>




namespace aae
{



/**
 *@brief The mesh_util class is a helper to load fbx meshes
 */
class mesh_util
{


public:
    mesh_util();



    /**
     * @brief ComputeTextureFilename will compute the filename of the texture
     * acording the where fbx meshes will look for their textures (.fbm folder
     * and .fbx folder)
     * @param texture_name is the name of the texture as
     * extracted from the fbx file
     * @param fbx_file_name is the name of the file
     * we are trying to load
     * @return will return the required texture filename to load the texture if
     * it can find the texture, otherwise null string
     */
    static QString ComputeTextureFilename(QString texture_name, QString fbx_file_name);


    /**
     * @brief QVector3DFromFbxVector3D will compute a QT version of
     * a 3d fbx vector
     * @param vec is the vector to be converted
     * @return
     */
    static QVector3D QVector3DFromFbxVector3D(FbxDouble3 vec);




};




}

#endif // MESH_UTIL_H
