#include "base.h"

Base::Base()
{

}
bool Base::intersect(int x, int y) {
    return  ( ((x > _Pos.x) && (x < _Pos.x + _Size.w) ) &&
              ((y > _Pos.y) && (y < _Pos.y + _Size.h)) ) ? true : false;
}
