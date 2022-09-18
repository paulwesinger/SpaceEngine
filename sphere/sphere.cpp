#include "sphere.h"


/*
 * File:   CSphere.cpp
 * Author: paul
 *
 * Created on 27. Oktober 2019, 20:03
 */

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "sphere.h"
#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../vecmath/vecmath.h"

using namespace glm;


static const GLchar * vs_source = {
"#version 440 core                              \n"
"layout (location=0) in vec3 vertex;            \n"
"layout (location=1) in vec3 color;             \n"
"layout (location=2) in vec2 tex;               \n"

"uniform mat4 mv;                               \n"

"out VS_OUT{                                    \n"
"       vec4 color;                             \n"
"       vec2 TexCoord;                          \n"
"} vs_out;                                      \n"

"void main(void) {                              \n"
"    float alpha = 1.0f;                         \n"
"    gl_Position = mv * vec4(vertex,1.0);       \n"
"    if (vertex.z < 0 ) {                       \n"
"       alpha = 0.3f;                           \n"
"    }                                          \n"
"    //vs_out.color = vec4(color,1.0);          \n"
"    vs_out.color = vec4(color,alpha);          \n"
"    vs_out.TexCoord =  tex;                    \n"
"}"
};

static const GLchar * fs_source = {
"#version 440 core                              \n"

"layout(binding=0) uniform sampler2D texture1;  \n"
"layout(binding=1) uniform sampler2D texture2;  \n"

"out vec4 fragcolor;                            \n"
"uniform vec4 changecolor;                      \n"

"in VS_OUT {                                    \n"
"   vec4 color;                                 \n"
"   vec2 TexCoord;                                   \n"
"}fs_in;                                        \n"

"void main(void) {                              \n"
"   // fragcolor =  changecolor;                \n"
"   fragcolor = mix(texture(texture1, fs_in.TexCoord), texture(texture2, fs_in.TexCoord), 0.8);"
"   fragcolor = fragcolor * changecolor;        \n"
"}                                              "
};

CSphere::CSphere() :
    Animate((vec3(0.0,0.0,0.0)),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec4(0.5,0.2,0.6,1.0)) {
   _CountPoints = 36;
   _Radius = 20.0f;

   float radians = glm::radians(45.0f);
   float aspect = 4.0f / 3.0f;
   float near= 0.1f ;
   float far = 100.0f;
   glm::mat4 pro = perspective(radians,aspect,near,far);

   //----------------------------------------------------------------------------------------------------
   //Standard Constructor darf Setup noch _NICHT aufrufen! Radius und Anzahl sind hier noch nicht bekannt
   //setUp();
   //----------------------------------------------------------------------------------------------------
}

CSphere::CSphere( int points) :
        Animate((vec3(0.0,0.0,0.0)),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec4(0.5,0.2,0.6,1.0)) {
   _CountPoints = points;
   _Radius      = 20.0f;
   float radians = glm::radians(45.0f);
   float aspect = 4.0f / 3.0f;
   float near= 0.1f ;
   float far = 100.0f;
   glm::mat4 pro = perspective(radians,aspect,near,far); //Standard
   setUp();
}
CSphere::CSphere( int points, GLfloat rad)
        : Animate((vec3(0.0,0.0,0.0)),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec4(0.5,0.2,0.6,1.0)) {
   _CountPoints = points;
   _Radius      = rad;
   float radians = glm::radians(45.0f);
   float aspect = 4.0f / 3.0f;
   float near= 0.1f ;
   float far = 100.0f;
   glm::mat4 pro = perspective(radians,aspect,near,far); //Standard
   setUp();
}

CSphere::CSphere(const CSphere& orig) {
}

CSphere::CSphere(vec3 origin, glm::mat4 pro)
    : Animate(origin,origin,origin,vec4(0.5,0.2,0.6,1.0))
{
    _CountPoints = 36;
    _Radius      = 20.0f;
    SetProjection( pro);
    setUp();
}
CSphere::CSphere(vec3 origin, glm::mat4 pro, int points)
    : Animate(origin,origin,origin,vec4(0.5,0.2,0.6,1.0))
{
    _CountPoints = points;
    _Radius      = 20.0f;
    SetProjection( pro);
    setUp();
}
CSphere::CSphere(vec3 origin, glm::mat4 pro, int points, GLfloat rad, Shader * shad)
    : Animate(origin,origin,origin,vec4(0.5,0.2,0.6,1.0))
{
    shader = shad;
    _CountPoints = points;
    _Radius      = rad;
    setUp();
}

CSphere::CSphere(vec3 origin, vec4 color, glm::mat4 pro)
    : Animate(origin,origin,origin,color) {
    _Radius      = 20.0f;
    _CountPoints = 36;
    setUp();
}
CSphere::CSphere(vec3 origin, vec4 color, glm::mat4 pro ,int points)
    : Animate(origin,origin,origin,color) {
    _Radius      = 20.0f;
    _CountPoints = points;
    setUp();
}
CSphere::CSphere(vec3 origin, vec4 color, glm::mat4 pro ,int points,GLfloat rad,Shader * shad)
    : Animate(origin,origin,origin,color) {
    shader = shad;
    _Radius      = rad;
    _CountPoints = points;
    setUp();
}

CSphere::~CSphere() {
    glDeleteVertexArrays(1, &_Vao);
    glDeleteBuffers(1, &_VertexBuffer);
    //glDeleteBuffers(1, &index_buffer);
 //   glDeleteProgram(shaderprogram);
}

void CSphere::setRadius(GLfloat rad){
    _Radius = rad;
}

void CSphere::setCountMeshPoints(int c) {
    _CountPoints = c;
}

void CSphere::SetColor(vec4 color) {
    _color = color; // in Baseobject
}
//virtuale MEthoden
void CSphere::Draw(Camera* cam ){

    if (_UseBlending) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
 //       glBlendFunc(GL_SRC_ALPHA, GL_BLEND_SRC_ALPHA);
    }

//    glEnable(GL_DEPTH_TEST);

   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA, GL_BLEND_SRC_ALPHA);

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);

   // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glFrontFace(_FrontFace_Mode);
    glUseProgram(currentShader);

    // Locate uniforms in shader
    int matrix_location = glGetUniformLocation(currentShader, "mv_matrix");
    int projectionloc = glGetUniformLocation(currentShader,"projection");
    int viewloc = glGetUniformLocation(currentShader,"view");

    color_location = glGetUniformLocation(currentShader,"triangleColor");
    int ortho_location;// = glGetUniformLocation(currentShader,"orthomatrix");

    // Model  Lightning
    int modellocation = glGetUniformLocation(currentShader,"model");
    int lightlocation = glGetUniformLocation(currentShader,"lightpos");
    int lightcolorlocation = glGetUniformLocation(currentShader,"lightcolor");
    int useTex2Location = glGetUniformLocation(currentShader,"useTexture_2");

    glUniform4f(color_location,GetColor().r,GetColor().g,GetColor().b,GetColor().a);

    glUniform1i(useTex2Location,0);


    glm::mat4 Model(1);

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

    //Model = glm::scale(Model,GetScale());



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
            glm::vec3 lightcolor = glm::vec3( 0.0,1.00,0.0);
            glUniform3f(lightlocation,lightpos.x,lightpos.y,lightpos.z);
            glUniform3f(lightcolorlocation,lightcolor.x,lightcolor.y,lightcolor.z);
        }

    //glm::mat4 mvp = GetProjection() * cam->GetView() * Model;
    //glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mvp));

    glUniformMatrix4fv(projectionloc,1,GL_FALSE,glm::value_ptr(GetProjection()));
    glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam->GetView()));

    glBindVertexArray(_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_Textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _Textures[1]);

    glPointSize(8);

    glPolygonMode(GL_FRONT_AND_BACK,GL_POINTS);//BaseObject::_PolgonMode);       //GL_FILL  , GL_POINT);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_BodyPoints);
    glDrawElements(_DrawMode,body.size() , GL_UNSIGNED_SHORT,0);  // BaseObject::DrawMode(GL_TRIANGLESTRIP)

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    if (_UseBlending) {
        glDisable(GL_BLEND);
        glBlendFunc(GL_ONE,GL_ZERO);
    }
}

// ===============================================
// Protected Functions
//================================================

// Adds adds the values to the given array ind couznts up index
void CSphere::Add2GPU(float* v, int &index, GLfloat vx, GLfloat vy, GLfloat vz) {
    v[index]    = vx;
    v[index+1]  = vy;
    v[index+2]  = vz;
    index +=3;
}

// Overloaded:
void CSphere::Add2GPU(float* v, int &index, glm::vec3 vec) {
    v[index]    = vec.x;
    v[index+1]  = vec.y;
    v[index+2]  = vec.z;
    index +=3;
}

void CSphere::Add2GPU(float* v, int &index, glm::vec2 vec) {
    v[index]    = vec.x;
    v[index+1]  = vec.y;
    index +=2;
}

void CSphere::calcStrip() {

    glm::vec3 meridianPoint;
    glm::vec3 breitengradpoint;

    float winkelmeridian     = 180.0f / _CountPoints;
    float winkelbreitengrad  = 360.0f / (_CountPoints*2 -1);
    float stepTexS           = 1.0f / (_CountPoints *2);        // waagrechte
    float stepTexT           = 1.0f / (_CountPoints + 1);       // Senkrechte
    float currentAngle       = 90.0f;

    int i,j;
    sVertexTexture vt;   // Structure für Texture Sphere
    sVertexColor   vc;

    for (i=0; i<_CountPoints*2;i++){
        meridianPoint.x = 0.0f;
        meridianPoint.y = _Radius;
        meridianPoint.z = 0.0f;

        vt.vector = meridianPoint;
        vt.color  = glm::normalize(vt.vector);

        if (i ==  (_CountPoints*2) -1)
            vt.tex.s = 1.0;
         else
            vt.tex.s = static_cast<float>(i) * stepTexS;
        vt.tex.t = 0.0;

        vc.vector  = meridianPoint;
        vertsTexture.push_back(vt);
        vertsColor.push_back(vc);
    }

    //---------------------------------------------
    // Body
    //---------------------------------------------
    for (i =1; i<_CountPoints; i++){

        currentAngle -= winkelmeridian;

        glm::vec2 mPoint;
        calccircle(_Radius, currentAngle, mPoint);
        meridianPoint.x = mPoint.x;
        meridianPoint.y = mPoint.y;
        meridianPoint.z = 0.0f;

        vt.vector = meridianPoint;
        vt.color  = glm::normalize(vt.vector);
        vt.tex.s = 0.0f;
        vt.tex.t = static_cast<float>(i) * stepTexT;

        vc.vector  = meridianPoint;
        vertsTexture.push_back(vt);
        vertsColor.push_back(vc);

        for (j=1; j < (_CountPoints*2); j++) {

            glm::vec2 lPoint;
            calccircle(meridianPoint.x, static_cast<float>(j)* winkelbreitengrad,lPoint);

             // Man könnte das ganze auch gleich direkt in das array fürden GPU Mem schreiben
             // .. ist aber so leichter zu lesen
             breitengradpoint.x = lPoint.x;//latitudePoints.at(j).x;
             breitengradpoint.y = meridianPoint.y;
             breitengradpoint.z = lPoint.y;//latitudePoints.at(j).y;
             // Texture , diesmal nur u koordinate , v bleibt erstmal

             if (j ==  (_CountPoints*2) -1)
                vt.tex.s = 1.0f; //static_cast<float>(j) * stepTexS;
             else
                 vt.tex.s = static_cast<float>(j) * stepTexS;

             vt.tex.t = static_cast<float>(i) * stepTexT;

             vt.vector = breitengradpoint;
             vt.color = glm::normalize(vt.vector);

             vc.vector = breitengradpoint;
             vertsTexture.push_back(vt);
             vertsColor.push_back(vc);
        }
    }

    for (i=0; i < _CountPoints*2; i++){
        meridianPoint.x = 0.0f;
        meridianPoint.y =  -_Radius;
        meridianPoint.z = 0.0f;

        vt.vector = meridianPoint;
        vt.color  = glm::normalize(vt.vector);
        vt.tex.s = static_cast<float>(i) * stepTexS;
        vt.tex.t = 1.0;

        vc.vector  = meridianPoint;
        vertsTexture.push_back(vt);
        vertsColor.push_back(vc);
    }
}


void CSphere::setUp() {

    calcStrip();

    // Neu mit std::vector
    glGenVertexArrays(1,&_Vao);
    glBindVertexArray(_Vao);
    // Vertex Buffer
    glGenBuffers(1,&_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 vertsTexture.size() * sizeof(sVertexTexture),
                 &vertsTexture[0],
                 GL_DYNAMIC_DRAW);


    // Vertex
    glVertexAttribPointer(0,3,GL_FLOAT, GL_TRUE, 8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //Color
    glVertexAttribPointer(1,3,GL_FLOAT, GL_TRUE, 8*sizeof(float),(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(float), (void*)(6 *sizeof(float)));
    glEnableVertexAttribArray(2);

    // -------------------------------------
    // Sphere body
    //--------------------------------------
    int x = 0;
    int step = (_CountPoints * 2);

    int i, j;

    for (j = 0; j <= _CountPoints - 1; j++) {  // -3

        for (i= 0; i < step; i++){
            body.push_back(i + x);
            body.push_back(i + x + step);
        }
        x += step;
    }

    glGenBuffers(1,&_BodyPoints);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_BodyPoints);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        body.size() * sizeof(GLushort),
                        &body[0],
                        GL_STATIC_DRAW);

    // Alles reseten
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}
