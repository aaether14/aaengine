#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H




#include <QVector3D>
#include <QDataStream>
#include <QDebug>




namespace aae
{



/**
 *@brief The bounding_box class will provide functionality for taking account
 *of kd bounding boxes in the scene
 */
template <class T>
class bounding_box
{


    /**
     * @brief m_min stores the minimum point in space of the bounding_box
     */
    T m_min;


    /**
     * @brief m_max stores the maximum point in space of the bounding_box
     */
    T m_max;



public:


    /**
     * @brief bounding_box is the constructor of the bounding box
     * @param min is the minimum point in space of the bounding_box
     * @param max is the maximum point in space of the bounding_box
     */
    bounding_box(const T &min,
                 const T &max){


        m_min = min;
        m_max = max;


    }


    /**
     * @brief bounding_box is a basic constructor
     */
    bounding_box(){

        m_min = T();
        m_max = T();

    }



    /**
     * @brief GetMin will return the minimum point of the bounding_box
     * @return m_min;
     */
    inline const T &GetMin() const{
        return m_min;
    }



    /**
     * @brief GetMax will return the maximum point of the bounding_box
     * @return m_max;
     */
    inline const T &GetMax() const{
        return m_max;
    }



    /**
     * @brief SetMin will set the minimum point of the bounding_box
     * @param min is the point to set m_min
     */
    inline void SetMin(const T &min){
        m_min = min;
    }



    /**
     * @brief SetMax will set the maximum point of the bounding_box
     * @param max is the point to set m_max
     */
    inline void SetMax(const T &max){
        m_max = max;
    }



    /**
     * @brief expand will expand the bounding_box to contain the provided point
     * @param point is the point to expand the bounding_box
     */
    inline void expand(const T &point){

    }



};


/**
 * @brief bounding_box3d is a typedef for a 3d bounding box
 */
typedef bounding_box<QVector3D> bounding_box3d;




template <class T>
QDataStream &operator <<(QDataStream &out, const bounding_box<T> & bbox){

    out << bbox.GetMin() << bbox.GetMax();
    return out;

}




template <class T>
QDataStream &operator >>(QDataStream &in, bounding_box<T> & bbox){


    T min, max;
    in >> min >> max;


    bbox.SetMin(min);
    bbox.SetMax(max);
    return in;


}




template <class T>
QDebug operator <<(QDebug out, const bounding_box<T> &bbox){


    out.nospace() << "aae::bounding_box(" << bbox.GetMin() << ", " << bbox.GetMax() << ")";
    return out;


}






}






#endif // BOUNDING_BOX_H
