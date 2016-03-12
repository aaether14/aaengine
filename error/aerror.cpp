#include <error/aerror.hpp>




namespace aae
{





AError::AError(QString msg) : std::runtime_error(msg.toStdString())
{



}




AError::AError(const char *msg) : std::runtime_error(msg)
{


}









}
