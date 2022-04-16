#ifndef PARTIKELENGINE_H
#define PARTIKELENGINE_H

#include <GL/glew.h>
#include "../cube/cube.h"
#include "../Animate/animate.h"
#include "../camera/camera.h"
#include "../projection/projection.h"
#include <glm/glm.hpp>

typedef struct {

    glm::vec3 emissionPoint;
    glm::vec3 direction;
    glm::vec4 color;
    glm::vec3 actPos;
    int textureID;
    float lifeTime;
    float velocity;

    CCube * cube;
} sPartikel;


class PartikelEngine
{
public:
    PartikelEngine(glm::mat4 pro);
    PartikelEngine(glm::mat4 pro, int count);
    ~PartikelEngine();

    void emit(int id);
    void destroy(int id);

    void Render(Camera * camera);

private:
    std::vector<sPartikel> partikel;
    int count;
};

#endif // PARTIKELENGINE_H
