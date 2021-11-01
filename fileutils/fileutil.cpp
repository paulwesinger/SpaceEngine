#include "fileutil.h"


/*
 * File:   fileUtil.cpp
 * Author: paul
 *
 * Created on 11. April 2019, 21:03
 */

#include <vector>
#include <stdio.h>
#include "fileutil.h"
#include "../utils/utils.h"
#include "../logs/logs.h"
using namespace std;

const int MAXLINES = 100;

fileUtil::fileUtil() {
    clear();
}

fileUtil::fileUtil(const fileUtil& orig) {
}

fileUtil::~fileUtil() {
}

void fileUtil::clear() {
    flags = fstream::app ; // standard Flag
    fileopen = false;
    filename = "";
}
bool fileUtil::readShaderSource(string & s, string path){
    FILE * pFile;
    char buffer[100];
    pFile = fopen(path.c_str(),"r");

    if ( pFile == nullptr)
        return false;

    while ( ! feof(pFile) ) {
       if ( fgets (buffer , 100 , pFile) == NULL ) break;
       std::string st(buffer);
       s += st;
    }
    return true;
}

bool fileUtil::writeline(string datei,string text) {
    ofstream os (datei.c_str(), flags);
    if ( os.is_open()) {
        char * buffer = new char[text.size()];
        int size = text.size();
        text.copy(buffer,size);
        os.write(buffer,size);
        os.close();
        loginfo ("Writing Text to file " + datei + " ... done","fileUtil");
        loginfo ("File " + datei + " ... closed","fileUtil");
        return true;
    }
    else
        logwarn("File " + datei + " was not open ... failure!","fileutil" );

    return false;
}

std::string fileUtil::Parse(std::string line, std::string delString, std::string spacestring) {
    std::string help = delString + spacestring;

    return help.erase(0,help.length());
}

int fileUtil::ParseToint(std::string line, std::string delString, std::string spacestring) {
    std::string help = Parse(line,delString,spacestring);
    return StringToInt(help);
}

bool fileUtil::readLine(string datei,std::vector<std::string> &lines) {
    ifstream is;
    string line;

    is.open(datei.c_str());
    if (is.is_open() ) {
        int i = 0;
        while (getline(is,line)) {
           lines.push_back(line);
           i++;
        }
        is.close();

        loginfo("Loaded " + IntToString(i) + " entries","fileUtil :: readline" );
        loginfo ("Reading Data from file " + datei + " ... done","fileUtil :: readLine");
        logEmptyLine();

        return  true;
    }











    /*
    //vector<string> stringlist;
    int i =0;
    if ( is.is_open()) {
        while ( ! is.eof() && i < MAXLINES ) {  // sicherheitsabbruch !!!
            char buffer[512];
            std::string st;
            is.getline(buffer,512);
            if ( is.gcount() > 0 ) {
                st = (string)buffer;
                lines.push_back(st);


            }
            i++;
        }
        loginfo("Loaded " + IntToString(i) + " entries" );
        loginfo ("Reading Data from file " + datei + " ... done","fileUtil");
        logEmptyLine();

        is.close();
        return true;
    }
    */
    else {
        logwarn("Warning : Konnte Datei " + datei + " nicht öffnen","fileutil");
        return  false;
    }
}

void fileUtil::setFlags(ifstream::openmode fileflags) {  // falls trunc gewünscht
    flags = fileflags;
}
