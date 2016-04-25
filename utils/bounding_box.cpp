#include <utils/bounding_box.hpp>




namespace aae
{




bounding_box::bounding_box(const QVector3D &min,
                           const QVector3D &max)
{


    m_min = min;
    m_max = max;


}





void bounding_box::expand(const QVector3D &point)
{





}






}
