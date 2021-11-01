#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

enum LIGHTS {
    AMBIENTE  =  0,
    SPOTLIGHT,
    DIFFUSELIGHT,
    SPECLIGHT
 };



class light
{
public:
    light();
    light(int type);
    void setLightOn(bool on);
    void setColor(glm::vec3 col);
    void setPos(glm::vec3 pos);
    void changeType(int t);

    void moveLight(glm::vec3 stepTo);  // Attention: this func adds stepto to the current pos ..
    void rotateLight(glm::vec3 stepDegree); // thge same like above

    glm::vec3 getPos();
    glm::vec3 getColor();

protected:
    glm::vec3 _Pos;
    glm::vec3 _Direction;
    glm::vec3 _Color;

    glm::vec3 _DirectionNormal;
    bool _LightOn;
private:
    void init();

    int _LightType;
    float _Lightstrength;
};

#endif // LIGHT_H
