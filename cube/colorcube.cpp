#include "colorcube.h"
/*
 * File:   CCube.cpp
 * Author: paul
 *
 * Created on 27. Mai 2018, 11:17
 */
#include <stdlib.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../imageloader/loadimage.h"


static const GLushort vertex_NormalIndices[] =
{
    2, 1, 0,   //Back
    5, 4, 3,

    6, 7, 8,   //Front
    9, 10, 11,

    12, 13, 14,
    15, 16, 17,

    20, 19, 18,
    23, 22, 21,

    24, 25, 26,
    27, 28, 29,

    32, 31, 30,
    35, 34, 33
};

static const GLfloat vertex_normals[] = {
     // x,y,z                normales           color
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0, 1.0, 1.0,
     1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0, 1.0, 1.0,
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0, 1.0, 1.0,
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0, 1.0, 1.0, // Back
    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0, 1.0, 1.0,
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0, 1.0, 1.0,

    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0, 1.0, 1.0,
     1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0, 1.0, 1.0, //Front
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0, 1.0, 1.0,
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0, 1.0, 1.0,
    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0, 1.0, 1.0,
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0, 1.0, 1.0,

    -1.0f,  1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  1.0, 1.0, 1.0,
    -1.0f,  1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  1.0, 1.0, 1.0,
    -1.0f, -1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  1.0, 1.0, 1.0,
    -1.0f, -1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  1.0, 1.0, 1.0,
    -1.0f, -1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  1.0, 1.0, 1.0,  // LEFT
    -1.0f,  1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  1.0, 1.0, 1.0,

     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0, 1.0, 1.0,
     1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0, 1.0, 1.0,
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0, 1.0, 1.0,   // Right
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0, 1.0, 1.0,
     1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0, 1.0, 1.0,
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0, 1.0, 1.0,

    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0, 1.0, 1.0,
     1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0, 1.0, 1.0,    //Bottom
     1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0, 1.0, 1.0,
     1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0, 1.0, 1.0,
    -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0, 1.0, 1.0,
    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0, 1.0, 1.0,

    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0, 1.0, 1.0,
     1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0, 1.0, 1.0,   //TOP
     1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0, 1.0, 1.0,
     1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0, 1.0, 1.0,
    -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0, 1.0, 1.0,
    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0, 1.0, 1.0
};

/*

 */
// Vertex Shader für Ortho Mode
static const GLchar * orthovs_source = {
    "#version 420 core                          \n"
    "layout(location=0) in vec3 position;       \n"
    "layout(location=2) in vec2 tex;            \n"
    "out vec2 TexCoords;                        \n"
    "uniform mat4 orthomatrix;                  \n"
//     "uniform mat4 viewmatrix;                   \n"

    "void main(void)                            \n"
    "{                                          \n"
    "   gl_Position = orthomatrix * vec4(position.xy,0.0,1.0); \n"
    "   TexCoords = vec2(tex.x,tex.y);  \n"
    "}                                            "
};

static const GLchar *orthofs_source = {
    "#version 420 core                          \n"
    "layout(location=1) in vec3 col;            \n"

    "in vec2 TexCoords;                         \n"
    "out vec4 color;                            \n"
    "uniform sampler2D texture1;                 \n"

    "void main()                                \n"
    "{                                          \n"
    "    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture1, TexCoords).r); \n"
    "    color = vec4(col,1.0) * sampled ;//vec4(col, 1.0) * sampled;   \n"
    "}                                            "
};
// Standard Constructors and Destructor

CColorCube::CColorCube()  :Animate() {

   shader = new Shader;
   float radians = glm::radians(45.0f);
   float aspect = 4.0f / 3.0f;
   float near= 0.1f ;
   float far = 10000.0f;
   glm::mat4 pro = glm::perspective(radians,aspect,near,far); //Standard
 //  SetProjection(pro);
   Init();
}

CColorCube::CColorCube(const CColorCube& orig,glm::mat4 pro)
    : Animate ( vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec4(0.5,0.2,0.6,1.0)) {
    shader = new Shader;
    SetProjection(pro);
    Init();
}

CColorCube:: CColorCube(glm::vec3(origin),glm::mat4 pro)
        : Animate (origin,origin,origin,vec4(0.5,0.2,0.6,1.0)) {
    shader = new Shader;
    SetProjection(pro);
    Init();
}

CColorCube:: CColorCube(glm::vec3(origin),vec4 color, glm::mat4 pro)
        : Animate (origin,origin,origin,color) {
    shader = new Shader;
    SetProjection(pro);
    Init();
}

CColorCube::~CColorCube() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &position_buffer);
    glDeleteBuffers(1, &index_buffer);
    glDeleteProgram(perspectiveColorShader);
    glDeleteProgram(perspectiveTextureShader);
    //delete shader;
}

// Owns Methodes
void CColorCube::Init() {

    _CountTextures = 0;
    // Buffers
    //Genererate vertexarray object and buffers
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    // positon buffer
    glGenBuffers(1,&position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER,position_buffer);
    // Vertex mit Normaler
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertex_normals),
                 vertex_normals,
                 GL_DYNAMIC_DRAW);

    // Index Buffer
    glGenBuffers(1,&index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  sizeof (vertex_NormalIndices),
                  vertex_NormalIndices,
                  GL_DYNAMIC_DRAW);

    // Vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normals
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),(void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE, 9 * sizeof (float),(void*)(6 *sizeof(float)));
    glEnableVertexAttribArray(2);

    //================================
    //Multitexturing erkunden...
    //================================
    GLint units;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&units);
    loginfo("Maximale Texture Units: " + IntToString(units) ,"Cube::Init");

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

}

void CColorCube::addLight(light *l) {
   BaseObject::addLight(l);
}

void CColorCube::Calc( float roty,float trans_x) {

}

void CColorCube::SetColor( vec4 color){
    _color = color;
}
void CColorCube::Draw(Camera * cam) {

    glUseProgram( currentShader);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    // Locate uniforms in shader
    mv_location = glGetUniformLocation(currentShader, "mv_matrix");
    int projectionloc = glGetUniformLocation(currentShader,"projection");
    int viewloc = glGetUniformLocation(currentShader,"view");
    color_location = glGetUniformLocation(currentShader,"triangleColor");
    // Model  Lightning
    int modellocation = glGetUniformLocation(currentShader,"model");
    int lightlocation = glGetUniformLocation(currentShader,"lightpos");
    int lightcolorlocation = glGetUniformLocation(currentShader,"lightcolor");

    glUniform4f(color_location,_color.r,_color.g, _color.b, _color.a);

    //Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model= glm::mat4(1.0f);

    if (  GetFirstTranslate() ) {

        Model = glm::translate(Model,GetTranslate());
        //printf ( "Cube::Draw glm::translate :  %f, %f ,%f \n",GetTranslate().x,GetTranslate().y,GetTranslate().z);
        Model = glm::rotate(Model, radians(GetRotate().x),vec3(1.0,0.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().y),vec3(0.0,1.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().z),vec3(0.0,0.0,1.0));
    }
    else {
        Model = glm::rotate(Model, radians(GetRotate().x),vec3(1.0,0.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().y),vec3(0.0,1.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().z),vec3(0.0,0.0,1.0));

        Model = glm::translate(Model,GetTranslate());
    }

    Model = glm::scale(Model,GetScale());


    if (_IsOrtho) {
  //      glm::mat4 view = glm::lookAt(vec3(0.0f,0.0f,0.1f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 0.0f));
  //      glm::mat4 mvp =  GetProjection() * view * Model;
  //      glUniformMatrix4fv(ortho_location, 1, GL_FALSE, glm::value_ptr(mvp));
    }
    else {
       glm::mat4 mvp =  GetProjection() * cam ->GetView() *  Model;
       glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mvp));
    }

    // -----------------------------------------
    // Lightning
    // -----------------------------------------
    glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(Model));

    if ( _Light != nullptr) {
        glm::vec3 c =   _Light->getColor();
        glm::vec3 p =   _Light->getPos();
        glUniform3f(lightlocation,p.x,p.y,p.z);
        glUniform3f(lightcolorlocation,c.x,c.y,c.z);
    }
    else {
        glm::vec3 lightpos = vec3(-10.0,2.0,-5.0);
        glm::vec3 lightcolor = glm::vec3( 0.0,1.0,0.0);
        glUniform3f(lightlocation,lightpos.x,lightpos.y,lightpos.z);
        glUniform3f(lightcolorlocation,lightcolor.x,lightcolor.y,lightcolor.z);
    }


    glUniformMatrix4fv(projectionloc,1,GL_FALSE,glm::value_ptr(GetProjection()));
    glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam->GetView()));

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer);
    glDrawElements( GL_TRIANGLES, sizeof(vertex_NormalIndices), GL_UNSIGNED_SHORT, 0);//GL_TRIANGLES
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}
