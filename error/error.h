#ifndef ERROR_H
#define ERROR_H

#include "../logs/logs.h"

class Error
{
public:
    static void Warning(bool isExpressionTrue,std::string message);
    static void Failed(bool isExpressionTrue,const std::string message, bool & errorflag );

private:

    Error() {}
};

#endif // ERROR_H
