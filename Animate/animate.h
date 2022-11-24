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

    void AnimateTranslate( uint elapsed) override;
    void AnimateRotate( uint32 elapsed) override;
    void AnimateScale( uint elapsed) override;

    void Scale(glm::vec3 s) override;
    void Translate(glm::vec3 t) override;
    void Rotate(glm::vec3 r) override;

protected:
    void init();
    bool _TranslateFirst;   // im Baseoibject löschen !!!

    void setSpeedPerSecond_RotX(float sx);
    void setSpeedPerSecond_RotY(float sy);
    void setSpeedPerSecond_RotZ(float sz);

private:
    glm::vec3 _RotSpeed;
    glm::vec3 _TransSpeed;
    glm::vec3 _ScaleSpeed;
};

#endif // ANIMATE_H
