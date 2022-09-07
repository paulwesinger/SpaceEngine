#ifndef WINDOW_H
#define WINDOW_H


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>

#include "../shaders/shader.h"
#include "../camera/camera.h"

#include "../defines.h"
#include "../base2d//base2d.h"


class Window : public Base2D {
    Window(int resX, int resy);
    Window(int resX, int resy,std::string path);


    virtual void Render();
    virtual void OnClick();
};

#endif
