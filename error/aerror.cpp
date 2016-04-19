#include <error/aerror.hpp>




namespace aae
{





AError::AError(const QString &msg) : std::runtime_error(msg.toStdString())
{



}




AError::AError(const char *msg) : std::runtime_error(msg)
{


}









}
