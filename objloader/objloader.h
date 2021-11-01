#ifndef COBJLOADER_H
#define COBJLOADER_H

#include <stdio.h>
#include <vector>
#include <string>

#include "../defines.h"
#include "glm/vec3.hpp"

enum {
    NO_ERROR = 0,
    NO_FILENAME,
    NO_VECDATA,
    NO_FACEDATA,
    NO_TEXTUREDATA,
    EMPTY_FILE,
    READ_ERROR
};

class COBJLoader
{
public:
    COBJLoader();
    COBJLoader(std::string filename);
    ~COBJLoader();

    void SetOBJFileName(std::string filename);
    int LoadOBJ();

    std::vector<TEXTURECOORDS>& TextureCoordinates();
    std::vector<VECTOR> & Vecs();
    std::vector<FACE> & Faces();
protected:
    std::vector<TEXTURECOORDS> texCoords;
    std::vector<VECTOR> vecs;
    std::vector<FACE> faces;

    VECTOR  ReadVec(std::string line, std::string key);
    TEXTURECOORDS  ReadTex(std::string line, std::string key);
    bool ReadFace(std::string line, std::string key, int & countfaces);

private:
    float ParseStringToFloat(std::string &line, std::string key, bool & ok);
    int getIndex(std::string &line);
    std::string castBufToString(std::string &s, size_t p);

    std::string _FileName;


};

#endif // COBJLOADER_H
