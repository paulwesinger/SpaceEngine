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
void Animate::setElapsed(uint el) {_Elapsed = el;}

void Animate::AnimateRotate(uint32 elapsed){

    glm::vec3 v;

    _rotate.x += _RotSpeed.x * elapsed;
    _rotate.y += _RotSpeed.y * elapsed;
    _rotate.z += _RotSpeed.z * elapsed;
    checkdegree(_rotate);

//    BaseObject::AnimateRotate(v);
}

void Animate::StepTranslate(vec3 step, uint elapsed){
    BaseObject::StepTranslate(step,elapsed);
}

void Animate::StepScale(vec3 step, uint elapsed){
    BaseObject::StepScale(step,elapsed);
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

