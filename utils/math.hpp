#ifndef MATH_H
#define MATH_H




#include <QObject>
#include <QMatrix4x4>





class Math : public QObject
{


    Q_OBJECT



public:



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




signals:




public slots:
};

#endif // MATH_H
