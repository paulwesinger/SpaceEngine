#ifndef CCUBE_H
#define CCUBE_H

/*
 * File:   CCube.h
 * Author: paul
 *
 * Created on 27. Mai 2018, 11:17
 */

#include <cstdio>
#include <vector>
#include <glm/glm.hpp>

#include "../shaders/shader.h"
#include "../baseobject/baseobject.h"
#include "../camera/camera.h"
#include "../shaders/shader.h"
#include "../lights/light.h"
#include "../Animate/animate.h"

using namespace glm;

class CCube : public Animate {
public:
    CCube();
    CCube(const CCube& orig,glm::mat4 pro);
    CCube(vec3 origin,glm::mat4 pro) ;
    CCube(vec3 origin , vec4 color, glm::mat4 pro);
    virtual ~CCube();
    virtual void Draw( Camera * cam);
    virtual void SetColor(vec4 color);

    void Init();
    void addLight(light * l);

private:
    int          orthoShader;
    GLuint       vao;

    GLuint          position_buffer;
    GLuint          index_buffer;
    GLint           mv_location;
    GLint           ortho_location;
    GLint           color_location; // Farbe im vertex Shader
    GLint           viewlocation;   // viewmatreix für orhomode
    int             vs ;
    int             fs;
    Shader *        shader;

    // Light
    //light *  _Light;  // Liste ?

    // Transformations
    vec3           _Trans;
    vec3           _Rotate;
    vec3           _Scale;
    vec4           _Color;
    // flags  --> ins BaseObject ??
    bool left;
 };


#endif // CCUBE_H
