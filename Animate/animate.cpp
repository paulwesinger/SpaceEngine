#include "animate.h"

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
}

void Animate::TranlateFirst() { _FirstTranslate = true; }
void Animate::RotateFirst(){ _FirstTranslate = false; }

void Animate::rotateX(float step) {}   //     vec3 _trans_step;//vec3 _rotate_step;//vec3 _scale_step; von Baseobject löschen
void Animate::rotateY(float step) {}
void Animate::rotateZ(float step) {}

void Animate::translateX(float step) {}
void Animate::translateY(float step) {}
void Animate::translateZ(float step) {}

void Animate::scaleX(float step) {}
void Animate::scaleY(float step) {}
void Animate::scaleZ(float step) {}

void Animate::scale(float stepx, float stepy, float stepz) {}
void Animate::translate(float stepx,float stepy, float stepz) {}
void Animate::rotate(float stepx, float stepy, float stepz) {}
