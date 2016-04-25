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
     * @param parent is the parent of the QObject
     */
    explicit Math(QObject *parent = 0);



    Q_INVOKABLE QMatrix4x4 scale(const QVector3D &xyz);



    Q_INVOKABLE QMatrix4x4 translate(const QVector3D &xyz);



    Q_INVOKABLE QMatrix4x4 rotate(const QVector3D &xyz);



    Q_INVOKABLE QMatrix4x4 transform(const QVector3D &translation_xyz,
                                     const QVector3D &rotation_xyz,
                                     const QVector3D &scaling_xyz);



    Q_INVOKABLE QMatrix4x4 camera(const QVector3D &position,
                                  const QVector3D &target,
                                  const QVector3D &up,
                                  const float &aspect_ratio,
                                  const float &fov,
                                  const float &near_plane,
                                  const float &far_plane);




signals:




public slots:
};





}

#endif // MATH_H
