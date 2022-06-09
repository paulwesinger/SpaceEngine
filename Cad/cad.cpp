#include "cad.h"


CadBase::CadBase() {}
CadBase::~CadBase() {}

void CadBase::setSyncPos(int pixels) {
    _SyncPos = pixels;
}

void CadBase::SyncPos(int &x, int &y) {

    // Das mal ohne syncwert , nur ganzzahlig durch 4
    x = x >> 3;
    y = y >> 3;
}

Cad::Cad()
{

}
Cad::~Cad() {}


