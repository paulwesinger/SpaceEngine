#include "error.h"


void Error::Warning(bool isExpressionTrue,std::string message) {
    if ( ! isExpressionTrue) {
        logwarn(message);
    }
}

void Error::Failed(bool isExpressionTrue,const std::string message, bool & errorflag) {
    if (! isExpressionTrue) {
        errorflag = true;
        logwarn(message);
        return;
    }
    errorflag = false;
}

