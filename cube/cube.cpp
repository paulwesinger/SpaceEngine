#include "cube.h"
/*
 * File:   CCube.cpp
 * Author: paul
 *
 * Created on 27. Mai 2018, 11:17
 */
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../imageloader/loadimage.h"


#include "cube.h"

static const GLushort vertex_indices[] =
{
    0, 1, 2,
    2, 1, 3,
    2, 3, 4,
    4, 3, 5,
    4, 5, 6,
    6, 5, 7,
    6, 7, 0,
    0, 7, 1,
    6, 0, 2,
    2, 4, 6,
    7, 5, 3,
    7, 3, 1
};

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

static const GLfloat vertex_positions[] =
{
  //    positions           - colors -          -texture -
    // Front plane
    -1.0f, -0.7f, -1.0f,   1.0f, 0.8f, 0.2f,    0.0,1.0,  //0
    -1.0f,  0.7f, -1.0f,   1.0f, 0.8f, 0.2f,    0.0,0.0,  //1
     1.0f, -0.7f, -1.0f,   1.0f, 0.8f, 0.9f,    1.0,1.0,  //2
     1.0f,  0.7f, -1.0f,   1.0f, 0.2f, 0.8f,    1.0,0.0,  //3
    // Back Plane
     1.0f, -0.7f,  1.0f,   1.0f, 0.3f, 0.7f,    1.0,1.0,  //4
     1.0f,  0.7f,  1.0f,   1.0f, 0.4f, 0.6f,    1.0,0.0,  //5
    -1.0f, -0.7f,  1.0f,   1.0f, 0.5f, 0.5f,    0.0,1.0,  //6
    -1.0f,  0.7f,  1.0f,   1.0f, 0.6f, 0.2f,    0.0,0.0   //7
};

static const GLfloat vertex_normals[] = {
     // x,y,z                normales           Color           texture
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0, 0.0,0.0 , 0.0, 0.0,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0, 0.0,0.0 , 1.0, 0.0,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0, 0.0,0.0 , 1.0, 1.0,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0, 0.0,0.0 , 1.0, 1.0,  // Back
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0, 0.0,0.0 , 0.0, 1.0,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0, 0.0,0.0 , 0.0, 0.0,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0, 1.0,0.0 ,0.0, 0.0,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  01.0, 1.0,0.0 ,1.0, 0.0,  //Front
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0, 1.0,0.0 ,1.0, 1.0,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0, 1.0,0.0 ,1.0, 1.0,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0, 1.0,0.0 ,0.0, 1.0,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0, 1.0,0.0 ,0.0, 0.0,

    -0.5f,  0.5f,  0.5f, -1.0f,  -1.0f,  0.0f, 0.0, 0.0,1.0 ,1.0, 1.0,
    -0.5f,  0.5f, -0.5f, -1.0f,  -1.0f,  0.0f, 0.0, 0.0,1.0 , 0.0, 1.0,
    -0.5f, -0.5f, -0.5f, -1.0f,  -1.0f,  0.0f, 0.0, 0.0,1.0 , 0.0, 0.0,
    -0.5f, -0.5f, -0.5f, -1.0f,  -1.0f,  0.0f, 0.0, 0.0,1.0 , 0.0, 0.0,
    -0.5f, -0.5f,  0.5f, -1.0f,  -1.0f,  0.0f, 0.0, 0.0,1.0 , 1.0, 0.0,   // LEFT
    -0.5f,  0.5f,  0.5f, -1.0f,  -1.0f,  0.0f, 0.0, 0.0,1.0 , 1.0, 1.0,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0, 0.0,0.0 , 1.0, 1.0,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0, 0.0,0.0 , 0.0, 1.0,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0, 0.0,0.0 , 0.0, 0.0,   // Right
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0, 0.0,0.0 , 0.0, 0.0,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0, 0.0,0.0 , 1.0, 0.0,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0, 0.0,0.0 , 1.0, 1.0,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0, 1.0,0.0 , 1.0, 1.0,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0, 1.0,0.0 , 0.0, 1.0,    //Bottom
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0, 1.0,0.0 , 0.0, 0.0,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0, 1.0,0.0 , 0.0, 0.0,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0, 1.0,0.0 , 1.0, 0.0,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0, 1.0,0.0 , 1.0, 1.0,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0, 0.0,1.0 , 1.0, 1.0,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0, 0.0,1.0 , 0.0, 1.0,   //TOP
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0, 0.0,1.0 , 0.0, 0.0,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0, 0.0,1.0 , 0.0, 0.0,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0, 0.0,1.0 , 1.0, 0.0,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0, 0.0,1.0 , 1.0, 1.0
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
#include <glm/glm.hpp>
    "void main()                                \n"
    "{                                          \n"
    "    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture1, TexCoords).r); \n"
    "    color = vec4(col,1.0) * sampled ;//vec4(col, 1.0) * sampled;   \n"
    "}                                            "
};
// Standard Constructors and Destructor

CCube::CCube()  :Animate() {

   shader = new Shader;
   Init();
}

CCube::CCube(const CCube& orig,glm::mat4 pro)
    : Animate ( vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec4(0.5,0.2,0.6,1.0)) {
    shader = new Shader;
    SetProjection(pro);
    Init();
}

CCube:: CCube(glm::vec3(origin),glm::mat4 pro)
        : Animate (origin,origin,origin,vec4(0.5,0.2,0.6,1.0)) {
    shader = new Shader;
    SetProjection(pro);
    Init();
}

CCube:: CCube(glm::vec3(origin),vec4 color, glm::mat4 pro)
        : Animate (origin,origin,origin,color) {
    shader = new Shader;
    SetProjection(pro);
    Init();

}

CCube::~CCube() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &position_buffer);
    glDeleteBuffers(1, &index_buffer);
    glDeleteProgram(perspectiveColorShader);
    glDeleteProgram(perspectiveTextureShader);
    glDeleteProgram(orthoShader);
    //delete shader;
}

// Owns Methodes
void CCube::Init() {

    // Ortho Shader
    vs = shader -> compileVertexShader (orthovs_source);
    fs = shader -> compileFragmentShader(orthofs_source);
    orthoShader = shader ->CreateProgram(vs,fs);

    if ( vs == 0 || fs == 0 || orthoShader == 0)
        logwarn("WARNING OrthoShader fehlgeschlagen !!", "Cubbe::Init" );
    else
        loginfo("OrthoShader erstellt ID= "+ IntToString(orthoShader),"Cube::Init");

    _CountTextures = 0;
    _Color = vec4(1.0f,1.0f,1.0f,1.0f);

    // Buffers
    //Genererate vertexarray object and buffers
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&position_buffer);
    glGenBuffers(1,&index_buffer);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,position_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer);

    // Vertex mit Normaler
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertex_normals),
                 vertex_normals,
                 GL_DYNAMIC_DRAW);

    // Index Buffer

    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  sizeof (vertex_NormalIndices),
                  vertex_NormalIndices,
                  GL_DYNAMIC_DRAW);

    // Vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normals
    glVertexAttribPointer(1,3, GL_FLOAT, GL_TRUE, 11* sizeof(float),(void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Color
    glVertexAttribPointer(2,3, GL_FLOAT, GL_TRUE, 11* sizeof(float),(void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Texture
    glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE, 11 * sizeof (float),(void*)(9 *sizeof(float)));
    glEnableVertexAttribArray(3);

    //================================
    //Multitexturing erkunden...
    //================================
    GLint units;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&units);
    loginfo("Maximale Texture Units: " + IntToString(units) ,"Cube::Init");

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void CCube::addLight(light *l) {
   BaseObject::addLight(l);
}


void CCube::SetColor( vec4 color){
    _Color = color;
}
void CCube::Draw(Camera * cam) {

    glUseProgram( currentShader);

    if (_UseBlending) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
    }
    // Locate uniforms in shader
    int matrix_location = glGetUniformLocation(currentShader, "mv_matrix");
    int projectionloc   = glGetUniformLocation(currentShader,"projection");
    int viewloc         = glGetUniformLocation(currentShader,"view");
    int hasTextureloc  = glGetUniformLocation(currentShader,"hasTexture");
    int color_location = glGetUniformLocation(currentShader,"triangleColor");
    //ortho_location = glGetUniformLocation(currentShader,"orthomatrix");

    // Model  Lightning
    int modellocation = glGetUniformLocation(currentShader,"model");
    int lightlocation = glGetUniformLocation(currentShader,"lightpos");
    int lightcolorlocation = glGetUniformLocation(currentShader,"lightcolor");
    int useTex2Location = glGetUniformLocation(currentShader,"useTexture_2");
    int useBlinnLocation = glGetUniformLocation(currentShader,"blinn");

    glUniform1i(hasTextureloc,_HasTextures);
    glUniform4f(color_location,_Color.r,_Color.g, _Color.b, _Color.a);
    glUniform1i(useBlinnLocation,_UseBlinn);

    if (_CountTextures >1 )
        glUniform1i(useTex2Location,true);
    else
        glUniform1i(useTex2Location,false);



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
        glm::mat4 view = glm::lookAt(vec3(0.0f,0.0f,0.1f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mvp =  GetProjection() * view * Model;
        glUniformMatrix4fv(ortho_location, 1, GL_FALSE, glm::value_ptr(mvp));
    }
    else {
       glm::mat4 mvp =  GetProjection() * cam ->GetView() *  Model;
       glUniformMatrix4fv(matrix_location, 1, GL_FALSE, glm::value_ptr(mvp));
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

    glFrontFace(_FrontFace_Mode);

    glUniformMatrix4fv(projectionloc,1,GL_FALSE,glm::value_ptr(GetProjection()));
    glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam->GetView()));

    if (_HasTextures) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_Textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _Textures[1]);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _Textures[2]);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, _Textures[3]);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, _Textures[4]);
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer);

    glDrawElements( GL_TRIANGLES, sizeof(vertex_NormalIndices), GL_UNSIGNED_SHORT, 0);//GL_TRIANGLES

    if (_HasTextures) {
        glBindTexture(GL_TEXTURE_2D,0);
        glActiveTexture(GL_TEXTURE0);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    if (_UseBlending ) {
        glDisable(GL_BLEND);
        glBlendFunc(GL_ONE,GL_ZERO);
    }
}
