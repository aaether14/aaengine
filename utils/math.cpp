#include <utils/math.hpp>






Math::Math(QObject *parent) : QObject(parent)
{

    setObjectName("gMath");

}





QMatrix4x4 Math::translate(QVector3D xyz)
{


    QMatrix4x4 result;
    result.translate(xyz);
    return result;


}




QMatrix4x4 Math::rotate(QVector3D xyz)
{

    QMatrix4x4 result;
    result.rotate(QQuaternion::fromEulerAngles(xyz));
    return result;

}




QMatrix4x4 Math::transform(QVector3D translation_xyz,
                           QVector3D rotation_xyz,
                           QVector3D scaling_xyz)
{


    QMatrix4x4 result;
    result.translate(translation_xyz);
    result.rotate(QQuaternion::fromEulerAngles(rotation_xyz));
    result.scale(scaling_xyz);
    return result;


}




QMatrix4x4 Math::scale(QVector3D xyz)
{


    QMatrix4x4 result;
    result.scale(xyz);
    return result;


}
