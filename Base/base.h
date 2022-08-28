#ifndef BASE_H
#define BASE_H


#include "../defines.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Base
{
public:
    Base();
    virtual bool  intersect(int x, int y);
protected:

    sPoint _Pos;
    sSize  _Size;
//glm::vec4   _Color;
};




#endif // BASE_H
