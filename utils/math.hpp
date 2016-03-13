#ifndef MATH_H
#define MATH_H




#include <QObject>
#include <QMatrix4x4>





namespace aae
{




/**
 *@brief The Math class is a simple math functions wrapper for Script usage
 */
class Math : public QObject
{


    Q_OBJECT



public:


    /**
     * @brief Math - basic constructor
     * @param parent
     */
    explicit Math(QObject *parent = 0);



    Q_INVOKABLE QMatrix4x4 scale(QVector3D xyz);



    Q_INVOKABLE QMatrix4x4 translate(QVector3D xyz);



    Q_INVOKABLE QMatrix4x4 rotate(QVector3D xyz);



    Q_INVOKABLE QMatrix4x4 transform(QVector3D translation_xyz,
                                     QVector3D rotation_xyz,
                                     QVector3D scaling_xyz);




    Q_INVOKABLE QMatrix4x4 scale(float x, float y, float z){return scale(QVector3D(x,y,z));}



    Q_INVOKABLE QMatrix4x4 scale(float factor){return scale(QVector3D(factor, factor, factor));}



    Q_INVOKABLE QMatrix4x4 translate(float x, float y, float z){return translate(QVector3D(x, y, z)); }




    Q_INVOKABLE QMatrix4x4 camera(QVector3D position,
                                  QVector3D target,
                                  QVector3D up,
                                  float aspect_ratio,
                                  float fov,
                                  float near_plane,
                                  float far_plane);




signals:




public slots:
};





}

#endif // MATH_H
