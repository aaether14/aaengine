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



    /**
     * @brief mesh_util - basic constructor
     */
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
    static float16 toFloat16(const float* arr){float16 v; memcpy(&v, arr, sizeof(float16)); return v;}






};




}

#endif // MESH_UTIL_H
