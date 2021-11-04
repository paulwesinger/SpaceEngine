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
    Cockpit(glm::mat4 proj);
    void setPosition(Camera * cam);
    glm::vec3 Position();
    void setProjectionMatrix(glm::mat4 mat);
    void Draw( Camera * cam);
    void InitShader(ShaderType s, GLuint prog);
    void setShader(ShaderType st);
    void setMesh(Animate * mesh);
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
    glm::mat4       matrix;

};

#endif // COCKPIT_H
