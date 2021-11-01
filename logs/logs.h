#ifndef LOGS_H
#define LOGS_H

#include <cstdio>
#include <string>

// -------------------------------------------------
// Info log für text und und text mit object
// -------------------------------------------------
void loginfo( std::string text);
void loginfo( std::string text, std::string object) ;
// log für images Grüner Text
void logimage( std::string text);
void logimage( std::string text, std::string object);
// -------------------------------------------------
// LogWarn ings für text und objects
// -------------------------------------------------
void logwarn( std::string text);
void logwarn( std::string text, std::string object);

void logEmptyLine(int count = 1);

#endif // LOGS_H
