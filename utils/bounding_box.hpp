#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H



#include <QVector3D>




namespace aae
{



/**
 *@brief The bounding_box class will provide functionality for taking account
 *of 3d bounding boxes in the scene
 */
class bounding_box
{


    /**
     * @brief m_min stores the minimum point in space of the bounding_box
     */
    QVector3D m_min;


    /**
     * @brief m_max stores the maximum point in space of the bounding_box
     */
    QVector3D m_max;



public:


    /**
     * @brief bounding_box is the constructor of the bounding box
     * @param min is the minimum point in space of the bounding_box
     * @param max is the maximum point in space of the bounding_box
     */
    bounding_box(const QVector3D &min,
                 const QVector3D &max);



    /**
     * @brief expand will expand the bounding_box to contain the provided point
     * @param point is the point to expand the bounding_box
     */
    void expand(const QVector3D &point);



};


}


#endif // BOUNDING_BOX_H
