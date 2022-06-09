#ifndef CAD_H
#define CAD_H

#include "defines.h"

class CadBase
{
public:
    CadBase();
    ~CadBase();
    void setSyncPos(int pixels); // Der Fang ...
    void SyncPos(int &x, int &y);

private:
    structCadBase sCB;
    LineType LineMode;


    int _SyncPos;

};

class Cad : public CadBase
{
public:
    Cad();
    ~Cad();
    //---------------------------------
    //Vektoren über xy setzen
    //---------------------------------
    void SetP1_xy(int x, int y);
    void SetP2_xy(int x, int y);

    //---------------------------------
    //Vektoren über xz setzen
    //---------------------------------
    void SetP1_xz(int x, int y);
    void SetP2_xz(int x, int y);
};

#endif // CAD_H
