/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plane3D.cpp
 * Author: paul
 * 
 * Created on 10. Mai 2019, 14:10
 */

#include<GL/glew.h>
#include "plane3D.h"

#include <SDL2/SDL_image.h>

#include "../logs/logs.h"
#include "../utils/utils.h"

static const GLchar * vs_src = {
    "#version = 440 core                    \n"
    "layout (location = 0) in vec3 vertex;  \n"
    "layout (location = 1) in vec3 color;   \n"
    "layout (location = 2) in vec2 uv;      \n"
    "out vec3 fragment;                     \n"
    "out vec2 tex;                          \n"
    "uniform mat4 projection;               \n"
    "void main(void)                        \n"
    "{                                      \n"
    "   gl_Position = vec4(vertex,1.0) * projection;     \n"
    "   fragment = color;                   \n"            
    "   tex = uv;                           \n"
};

static const GLchar * fs_src = {
    "#version = 440 core                    \n"
    "in vec3 fragment;                      \n"
    "in vec2 tex;                           \n"
    "uniform sampler2D frag;                \n"
    "out vec4 outcolor;                     \n"
            
    "void main(void)                        \n"
    "{                                      \n"
    "   vec4 texel = texture(frag,tex);     \n"
    "   outcolor = texel * vec4(fragment,1.0);\n"
    "}                                       "
};

    // --------------------  Vertices;
    static const GLfloat vertex_positions[] =
        {
                   
            -5.0f,  5.0f, 0.0f,   1.0f, 0.8f, 0.2f,    0.0,1.0,  
            -5.0f, -5.0f, 0.0f,   1.0f, 0.8f, 0.2f,    0.0,0.0,
             5.0f, -5.0f, 0.0f,   1.0f, 0.8f, 0.9f,    1.0,1.0,
             5.0f,  5.0f, 0.0f,   1.0f, 0.2f, 0.8f,    1.0,0.0,
        };
    static const GLushort vertex_indices[] =
        {
            0, 1, 2, 3
        };

// -------------------- Indexes
Plane3D::Plane3D(glm::mat4 pro) {
    shader = new Shader;
    projection = pro;
    Init();
}

Plane3D::Plane3D(const Plane3D& orig) {
}

Plane3D::~Plane3D() {
    delete shader;
}

void Plane3D::Init() {
    vs = shader->compileVertexShader( vs_src);
    fs = shader->compileFragmentShader(fs_src);
    program = shader->CreateProgram(vs,fs);
    if ( vs == 0 || fs == 0 || program == 0) 
        logwarn("WARNING PersoectiveShader fehlgeschlagen !!", "Cubbe::Init" );
    else
        loginfo("PerspectivShader erstellt","Cube::Init");
   
    glGenVertexArrays(1,&_VAO);
    glBindVertexArray(_VAO);
    glGenBuffers(1,&_VBO);
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);
    
    glBufferData(GL_ARRAY_BUFFER,
       sizeof(vertex_positions),
       vertex_positions,
       GL_STATIC_DRAW);
    
        // Index Buffer
    glGenBuffers(1,&_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  sizeof (vertex_indices),
                  vertex_indices,
                  GL_STATIC_DRAW);
    
}

