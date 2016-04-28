#include <error/aerror.hpp>




namespace aae
{





AError::AError(const QString &msg) : std::runtime_error(msg.toStdString())
{


    /**
    *The glorious nothing...
    */


}




AError::AError(const char *msg) : std::runtime_error(msg)
{


    /**
    *The glorious nothing...
    */


}









}
