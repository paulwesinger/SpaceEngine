#ifndef SKYBOX_H
#define SKYBOX_H


/*
 * File:   SkyBox.h
 * Author: paul
 *
 * Created on 08. Jänner 2019, 20:11
 */

#include <cstdio>
#include <string>

#include <SDL2/SDL_image.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

//#include "../camera/camera.h"
#include "../shaders/shader.h"

class SkyBox {
public:
    SkyBox(glm::mat4 pro);
    SkyBox(const SkyBox& orig);
    virtual ~SkyBox();
    virtual void Draw(glm::mat4 cameraview);
    bool Load(std::vector<std::string> &faces);
    void SetProjection(glm::mat4 pro);
private:

    bool LoadCubeMap(std::vector<std::string> &faces);
    unsigned int _SkyBoxID;
    glm::mat4 projection;

    GLint viewlocation;
    GLint projlocation;

    int shaderprog;
    int          vs;
    int          fs;

    GLuint          cubeVao;
    GLuint          skyboxVao;
    GLuint          cubeVertexbuffer;
    GLuint          skyboxVertexbuffer;
    GLuint          indexbuffer;
    Shader * shader;

    bool skyboxLoaded;
};

#endif // SKYBOX_H
