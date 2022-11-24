#include "animate.h"
#include "../vecmath/vecmath.h"

Animate::Animate() :
    BaseObject()
{
    init();
}

Animate::Animate(vec3 pos,glm::vec3 rotate,vec3 scale,vec4 col):
    BaseObject(pos, rotate, scale, col)

{
    init();
}

void Animate::init() {
    _HasAnimation = true;
    _RotSpeed.x = 0.0;
    _RotSpeed.y = 0.1;  // 1/10el grad prosec
    _RotSpeed.z = 0.05;

    _TransSpeed.x = 1.0;
    _TransSpeed.y = 1.0;
    _TransSpeed.z = 1.0;

    _ScaleSpeed.x = 1.0;
    _ScaleSpeed.y = 1.0;
    _ScaleSpeed.z = 1.0;
}

void Animate::TranlateFirst() { _FirstTranslate = true; }
void Animate::RotateFirst(){ _FirstTranslate = false; }

void Animate::AnimateRotate(uint elapsed){

    float factor = static_cast<float>(elapsed);
    _Rotate.x += _RotSpeed.x * factor;
    _Rotate.y += _RotSpeed.y * factor;
    _Rotate.z += _RotSpeed.z * factor;
    checkdegree(_Rotate);
}

void Animate::AnimateTranslate( uint elapsed){

    float factor = static_cast<float>(elapsed);
    _Translate.x += _TransSpeed.x * factor;
    _Translate.y += _TransSpeed.y * factor;
    _Translate.z += _TransSpeed.z * factor;
}

void Animate::AnimateScale( uint elapsed){

    float factor = static_cast<float>(elapsed);
    _Scale.x += _ScaleSpeed.x * factor;
    _Scale.y += _ScaleSpeed.y * factor;
    _Scale.z += _ScaleSpeed.z * factor;
}

void Animate::Scale(glm::vec3 s) {
    BaseObject::Scale(s);
}

void Animate::Translate(glm::vec3 t){
    BaseObject::Translate(t);
}

void Animate::Rotate(glm::vec3 r) {
    BaseObject::Rotate(r);
}

