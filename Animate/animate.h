#ifndef ANIMATE_H
#define ANIMATE_H

#include "../baseobject/baseobject.h"
#include <glm/glm.hpp>

using namespace glm;


class Animate : public BaseObject
{
public:
    Animate(vec3 pos,vec3 rotate,vec3 scale,vec4 col);
    Animate();

    void TranlateFirst();
    void RotateFirst();
    virtual void rotateX(float step);
    virtual void rotateY(float step);
    virtual void rotateZ(float step);

    virtual void translateX(float step);
    virtual void translateY(float step);
    virtual void translateZ(float step);

    virtual void scaleX(float step);
    virtual void scaleY(float step);
    virtual void scaleZ(float step);

    virtual void scale(float stepx, float stepy, float stepz);
    virtual void translate(float stepx,float stepy, float stepz);
    virtual void rotate(float stepx, float stepy, float stepz);

protected:
    void init();
    bool _TranslateFirst;   // im Baseoibject löschen !!!
};

#endif // ANIMATE_H
