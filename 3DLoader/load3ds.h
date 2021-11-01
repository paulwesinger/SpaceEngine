#ifndef CLOAD3DS_H
#define CLOAD3DS_H
#include "../defines.h"
#include <string>
#include <vector>

class C3DSLoad{
public:
    C3DSLoad();
    C3DSLoad(std::string filename);
    ~C3DSLoad();

    bool Load3DS(std::string filenmame);
    std::vector<TEXTURECOORDS>& TextureCoordinates();
    std::vector<VECTOR> & Vecs();
    std::vector<FACE> & Faces();

    int FaceCount();
    int VertexCount();
    int TextureCount();
    std::string Objectname();

private:
    int _FaceCount;
    int _VertexCount;
    int _TextureCount;
    std::string _Filename;
    std::string _Objectname;



    std::vector<TEXTURECOORDS> texCoords;
    std::vector<VECTOR> vecs;
    std::vector<FACE> faces;

    long filelength(int f);
};

#endif // CLOAD3DS_H
