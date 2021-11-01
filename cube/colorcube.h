#ifndef COLORCUBE_H
#define COLORCUBE_H

/*
 * File:   ColorCube.h
 * Author: paul
 *
 * Created on 27. Mai 2018, 11:17
 */

#include <cstdio>
#include <vector>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>

#include "../shaders/shader.h"
#include "../baseobject/baseobject.h"
#include "../camera/camera.h"
#include "../shaders/shader.h"
#include "../lights/light.h"
#include "../Animate/animate.h"

using namespace glm;

class CColorCube : public Animate {
public:
    CColorCube();
    CColorCube(const CColorCube& orig,glm::mat4 pro);
    CColorCube(vec3 origin,glm::mat4 pro) ;
    CColorCube(vec3 origin , vec4 color, glm::mat4 pro);
    virtual ~CColorCube();
    virtual void Draw( Camera * cam);
    virtual void Calc(float roty,float trans_x); // Check for Arguments
    virtual void SetColor(vec4 color);

    void Init();
    void addLight(light * l);

private:

    GLuint          vao;
    GLuint          position_buffer;
    GLuint          index_buffer;
    GLint           mv_location;

    GLint           color_location; // Farbe im vertex Shader
    GLint           viewlocation;   // viewmatreix für orhomode
    int             vs ;
    int             fs;
    Shader *        shader;

    // Light
    //light *  _Light;  // Liste ?

    // Transformations
   // vec3           _Trans;
   // vec3           _Rotate;
   // vec3           _Scale;

 };


#endif // CCUBE_H
