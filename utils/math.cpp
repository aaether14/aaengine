#include <utils/math.hpp>





namespace aae
{




Math::Math(QObject *parent) : QObject(parent)
{

    setObjectName("gMath");

}





QMatrix4x4 Math::translate(const QVector3D &xyz)
{


    QMatrix4x4 result;
    result.translate(xyz);
    return result;


}




QMatrix4x4 Math::rotate(const QVector3D &xyz)
{

    QMatrix4x4 result;
    result.rotate(QQuaternion::fromEulerAngles(xyz));
    return result;

}




QMatrix4x4 Math::transform(const QVector3D &translation_xyz,
                           const QVector3D &rotation_xyz,
                           const QVector3D &scaling_xyz)
{


    QMatrix4x4 result;
    result.translate(translation_xyz);
    result.rotate(QQuaternion::fromEulerAngles(rotation_xyz));
    result.scale(scaling_xyz);
    return result;


}




QMatrix4x4 Math::camera(const QVector3D &position,
                        const QVector3D &target,
                        const QVector3D &up,
                        const float &aspect_ratio,
                        const float &fov,
                        const float &near_plane,
                        const float &far_plane)
{


    QMatrix4x4 result;
    result.perspective(fov, aspect_ratio, near_plane, far_plane);
    result.lookAt(position,
                  target,
                  up);



    return result;


}




QMatrix4x4 Math::scale(const QVector3D &xyz)
{


    QMatrix4x4 result;
    result.scale(xyz);
    return result;


}






}
