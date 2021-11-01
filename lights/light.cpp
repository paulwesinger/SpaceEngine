#include "light.h"
#include "../vecmath/vecmath.h"
#include <glm/glm.hpp>
//#include <glm/vec3.hpp>

light::light()
{
    init();
}

light::light(int type) {
    init();
    changeType(type);
}

void light::init() {
    _LightType = AMBIENTE;
    _Pos = glm::vec3(0.0, 100.0, 0.0);
    _Color = glm::vec3(1.0, 1.0, 1.0);
    _Direction = glm::vec3(0.0, 0.0, 0.0);  // We look to the center of our universe
    _LightOn = true;
    _Lightstrength = 1.0f;

    _DirectionNormal =  + (glm::normalize(_Pos) );

}

void light::changeType(int t) {
    if (t > sizeof(LIGHTS) - 1 )

        _LightType = AMBIENTE;
    else
        _LightType = t;
}

void light::moveLight(glm::vec3 stepTo) {
    _Pos += stepTo;
}

void light::rotateLight(glm::vec3 stepDegree) {
    _Direction += stepDegree;
    checkdegree(_Direction.x);
    checkdegree(_Direction.y);
    checkdegree(_Direction.z);

    _DirectionNormal = glm::normalize(_Direction);
}

void light::setPos(glm::vec3 pos) {
    _Pos = pos;
}

void light::setColor(glm::vec3 col) {
    _Color = col;
}

void light::setLightOn(bool on) {
    _LightOn = on;
}

glm::vec3 light::getPos()   { return  _Pos; }
glm::vec3 light::getColor() { return  _Color; }

