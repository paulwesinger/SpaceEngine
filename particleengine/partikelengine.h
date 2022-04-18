#ifndef PARTIKELENGINE_H
#define PARTIKELENGINE_H

#include <GL/glew.h>
#include "../cube/cube.h"
#include "../Animate/animate.h"
#include "../camera/camera.h"
#include "../projection/projection.h"
#include "../shaders/shader.h"
#include <glm/glm.hpp>
#include "defines.h"

typedef struct {

    glm::vec3 emissionPoint;
    glm::vec3 direction;
    glm::vec4 color;
    glm::vec3 actPos;
    int textureID;
    Uint32 lifeTime;
    Uint32 UsedTime;
    float velocity;
    float weight;
    bool render;

    CCube * cube;
} sPartikel;


class PartikelEngine
{
public:
    PartikelEngine(glm::mat4 pro, ShaderType s);
    PartikelEngine(glm::mat4 pro, ShaderType s, int amount);
    ~PartikelEngine();

    void init();
    void setShader(ShaderType s,GLuint prog);
    void setEmissionTime(uint ms);
    void emit(int id,Camera * camera);
    void destroy(int id);

    void Render(Camera * camera,Uint32  el);

private:
    std::vector<sPartikel> partikel;
    int count;  // anzahl aller partikel
    int currentCount;  //momentane anzahl
    glm::mat4 projection;
        GLuint      perspectiveTextureShader,
                perspectiveColorShader,
                lightshader,
                lightcolorshader,
                lighttextureshader,
                glasshader,
                currentShader;

    Uint32  emissiontime;
     Uint32 elapsed;

};

#endif // PARTIKELENGINE_H
