/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plane3D.h
 * Author: paul
 *
 * Created on 10. Mai 2019, 14:10
 */

#ifndef PLANE3D_H
#define PLANE3D_H

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../shaders/shader.h"

class Plane3D {
public:
    Plane3D(glm::mat4 pro);
    Plane3D(const Plane3D& orig);
    virtual ~Plane3D();
protected:
    void Init();
private:
    int _ResX;
    int _ResY;
    
    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;
    
    Shader * shader;
    // ints for shader returns 
    int vs;
    int fs;
    int program;  // the linked shaders 
    
    GLint mv_projectloc;
    GLint mv_colorloc;
    GLint loc_model;
    
    glm::mat4 projection;
    unsigned int texture;

};

#endif /* PLANE3D_H */

