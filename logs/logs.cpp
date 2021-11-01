#include "logs.h"

void loginfo( std::string text) {
    printf( "\33[34m LogInfo : %s \n",text.c_str());
    printf("\33[0m");
}
void loginfo( std::string text, std::string object) {
    printf( "\33[34m LogInfo : %s :: %s \n",object.c_str(), text.c_str());
    printf("\33[0m");
}
// log ausgabe für Images -> Grün
void logimage( std::string text) {
    printf( "\33[32m LogInfo : %s \n",text.c_str());
    printf("\33[0m");
}
void logimage( std::string text, std::string object) {
    printf( "\33[32m LogInfo : %s :: %s \n",object.c_str(), text.c_str());
    printf("\33[0m");
}
// -------------------------------------------------
// LogWarn ings für text und objects
// -------------------------------------------------
void logwarn( std::string text){
    printf("\33[35m LogWarn : %s \n", text.c_str());
    printf("\33[0m");
}
void logwarn( std::string text, std::string object) {
    printf("\33[35m LogWarn : %s ::  %s \n", object.c_str(), text.c_str());
    printf("\33[0m");
}

void logEmptyLine(int count) {
    for (int i = 0; i < count; i++)
        printf("\n");

}
