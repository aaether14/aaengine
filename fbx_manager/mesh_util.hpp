#ifndef MESH_UTIL_H
#define MESH_UTIL_H



#include <aae_defines.hpp>



#include <QString>
#include <QVector3D>
#include <QFileInfo>



#ifdef AAE_USING_FBX
#include <fbxsdk.h>
#endif




namespace aae
{



namespace mesh_util
{


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
    QString ComputeTextureFilename(QString texture_name, QString fbx_file_name);



#ifdef AAE_USING_FBX
    /**
     * @brief QVector3DFromFbxVector3D will compute a QT version of
     * a 3d fbx vector
     * @param vec is the vector to be converted
     * @return
     */
    QVector3D QVector3DFromFbxVector3D(FbxDouble3 vec);
#endif



    /**
    @brief float16 is a typedef to the 16 float array, it is needed in order to
    convert QMatrix4x4 to something we can send to the shader
    */
    typedef struct float16 { float m[16]; } float16;
    /**
     * @brief toFloat16 converts a float array to float16 typedef
     * @param arr is the float data
     * @return returns the float16 block
     */
    inline float16 toFloat16(const float* arr){float16 v; memcpy(&v, arr, sizeof(float16)); return v;}






}




}

#endif // MESH_UTIL_H
