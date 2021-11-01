#include <stdio.h>
#include <cstring>
#include "objloader.h"
#include "../fileutils/fileutil.h"
#include "../utils/utils.h"
#include "../logs/logs.h"

COBJLoader::COBJLoader() {
    _FileName = "NO FILE";
}

COBJLoader::COBJLoader(std::string filename) {
    _FileName = filename;
}

COBJLoader::~COBJLoader(){
    texCoords.clear();
    faces.clear();
    vecs.clear();
}

int COBJLoader::LoadOBJ() {
    fileUtil * fu = new fileUtil();
    std::vector<std::string> lines;
    if (_FileName == NO_FILE )
        return NO_FILENAME;

    if ( ! fu->readLine(_FileName,lines) )
        return READ_ERROR;

    if (lines.empty())
        return  EMPTY_FILE;
    // Bis jetzt alles gut ...


    for ( uint i = 0; i < lines.size(); i++) {

        //std::string line = lines.at(i);
        std::string line = lines.at(i);
        // checken ob  '#', 'v' 'vt' 'f' oder andere...... die nicht ausgewertet werden
        // erstmal die ersten 3 zeichen in den Buffer kopieren und testen:
        char * cstr = new char [line.length()+1];
        std::strcpy (cstr, line.c_str());

        // Viele if's...

        std::string st;
        st.append(cstr,2);

        if (st == "v " ) {  // Vectors
            line.erase(0,2);  // erease v+leer -> übrig ist x, y, z
            VECTOR v = ReadVec(line," ");
        }
        else
            if (st == "vt") {// textures
                // erstmal vt+ leer löschen
                line.erase(0,3);
                TEXTURECOORDS t = ReadTex(line," ");

            }
            else
                if ( st == "vn") { // normale
                    line.erase(0,3);
                    VECTOR v = ReadVec(line," ");
                }
                else
                    if (st == "f "){ // face
                        line.erase(0,2);
                        int countVecs = 0; // manchmal 3, manchmal 4 und so weiter...
                        bool ok = ReadFace(line," ",countVecs);
                    }

    }
    return NO_ERROR;
}

bool COBJLoader::COBJLoader::ReadFace(std::string line, std::string key, int &countfaces)
{
    bool ok = false;
    int i = 0;

    // format n1/n2/n3 n1/n2/n3/ n1/n2/n3 .........
    // n1 = vectorindex
    // n2 = texturcoordinatenindex
    // n3 = normaleindex
    // das ganze dann 3, (Triangle) oder 4 (linestrip) , mehr... ?

    std::vector<int> vi;
    std::vector<int> ti;
    std::vector<int> ni;

    std::size_t pos = line.find(" ",0);
    std::string st;
    logwarn("Argument line" + line );

    while (pos != line.npos && countfaces <  10) {

        std::string st = castBufToString(line,pos);

        int f = getIndex(st);     // n1 = Vector index
        int t = getIndex(st);     // n2 = Texturkoordinaten index
        int n = getIndex(st);     // n3 = Normalen index

        countfaces ++;

        FACE face;


        logwarn("vecindex " + IntToString(f) );
        logwarn("texindex " + IntToString(t) );
        logwarn("normalindex " + IntToString(n) );
        logEmptyLine();
     //   faces.push_back(face);
        pos = line.find(" ",0);
    }

    st = castBufToString(line,pos);

    int f = getIndex(st);     // n1 = Vector index
    int t = getIndex(st);     // n2 = Texturkoordinaten index
    int n = getIndex(st);     // n3 = Normalen index
    countfaces ++;
    return true;
}

std::string COBJLoader::castBufToString(std::string &s, size_t p) {
    char buf[50];
    s.copy(buf,p);
    s.erase(0,p+1);
    std::string st(buf);
    return st;
    //return (std::string) buf;
}

int COBJLoader::getIndex(std::string &line){

    int i = 0;
    std::size_t pos = line.find("/",0);
    if (pos != line.npos) {
        return StringToInt(castBufToString(line,pos));
    }
    return StringToInt(line); //StringToInt((std::string) buf);
}


VECTOR COBJLoader::ReadVec(std::string line, std::string key) {


    VECTOR v;
    bool ok;
    // Format: "x y z"
    // Finde den das nächste leerzeichen:
    v.x = ParseStringToFloat(line, key, ok);
    v.y = ParseStringToFloat(line, key,ok);
    v.z = ParseStringToFloat(line,"",ok);

    logwarn("ReadVec x " + FloatToString(v.x) );

    logwarn("ReadVec y " + FloatToString(v.y) );

    logwarn("ReadVec z " + FloatToString(v.z) );
    logEmptyLine();


    return  v;
}

TEXTURECOORDS COBJLoader::ReadTex(std::string line, std::string key) {
    // FORMAT vt u v
    TEXTURECOORDS tex;
    bool ok = false;

    tex.u= ParseStringToFloat(line,key,ok);
    tex.v= ParseStringToFloat(line,"",ok);
    return tex;
}



float COBJLoader::ParseStringToFloat(std::string &line, std::string key, bool & ok) {

    ok = false;

    if ( key != "") {
        std::size_t pos = line.find(key,0);
        return StringToFloat(castBufToString(line,pos));
    }

    return StringToFloat(line);
}


void COBJLoader::SetOBJFileName(std::string filename) {
    _FileName = filename;
}


