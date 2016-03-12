#ifndef AERROR_H
#define AERROR_H




#include <stdexcept>
#include <QString>



namespace aae
{





/**
 * @brief The AError class will provide functionality for exception handling
 */
class AError : public std::runtime_error
{




public:


    /**
     * @brief AError is a basic constructor for QString
     * @param msg is the error message
     */
    AError(QString msg);



    /**
     * @brief AError is a basic constructor for const char*
     * @param msg is the error message
     */
    AError(const char * msg);







};


}


#endif // AERROR_H
