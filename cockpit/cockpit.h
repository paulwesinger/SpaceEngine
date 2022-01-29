#ifndef COCKPIT_H
#define COCKPIT_H

#include <glm/glm.hpp>
#include "../cube/cube.h"
#include "../Animate/animate.h"
#include "../camera/camera.h"
#include "../projection/projection.h"


class Cockpit
{
public:
    Cockpit(glm::mat4 proj,glm::vec3 position);
    void setPosition(Camera * cam);
    glm::vec3 Position();
    bool HasMesh();
    void setProjectionMatrix(glm::mat4 mat);
    void Draw( Camera * cam);
    void Rotate(glm::vec3 rot);
    void Steprotate(float step);
    void Translate(glm::vec3 tran);
    void InitShader(ShaderType s, GLuint prog);
    void setShader(ShaderType st);
    void setMesh(Animate * mesh);
    void SetDir(glm::vec3 dir);
    Animate * getCockpitMesch();
protected:
    Animate * Mesh;  // armaturenbrett
    glm::vec3 transFront;

    GLuint shaderprog_color;
    GLuint shaderprog_tex;
    GLuint shaderprog_normals;
    GLuint shaderprog_color_normal;

private:
    void init();
    glm::vec3       _Position;
    glm::vec3       _Rotation;
    glm::vec3       _Translation;
    glm::vec3       _Dir;
    glm::mat4       matrix;
    float           _StepRotate;

};

#endif // COCKPIT_H
