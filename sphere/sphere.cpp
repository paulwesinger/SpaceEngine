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
   glm::mat4 pro = perspective(radians,aspect,near,far); //Standard
   setUp();
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

void CSphere::SetColor(vec4 color) {
    _color = color; // in Baseobject
}
//virtuale MEthoden
void CSphere::Draw(Camera* cam ){

//    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glFrontFace(GL_CCW);

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

    glUniform4f(color_location,GetColor().r,GetColor().g,GetColor().b,GetColor().a);

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

    //glFrontFace(GL_CW);

    glBindVertexArray(_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_Textures[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _Textures[0]);

    glPointSize(8);

    glPolygonMode(GL_FRONT_AND_BACK,BaseObject::_PolgonMode);       //GL_FILL  , GL_POINT);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_BodyPoints);
    glDrawElements(_DrawMode,body.size(),GL_UNSIGNED_SHORT,0);

    glBindTexture(GL_TEXTURE_2D,0);
    glActiveTexture(GL_TEXTURE0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glDisable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ZERO);
    glFrontFace(GL_CCW);
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
    float winkelbreitengrad  = 360.0f / (_CountPoints*2);
    float stepTexS           = 1.0f / (_CountPoints *2);  // waagrechte
    float stepTexT           = 1.0f / _CountPoints;       // Senkrechte
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
        vt.tex.t = 1.0;

        vc.vector  = meridianPoint;
        vertsTexture.push_back(vt);
        vertsColor.push_back(vc);

    }


    //---------------------------------------------
    // Body
    //---------------------------------------------
    for (i =1; i<_CountPoints-1; i++){

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
             vt.tex.s = static_cast<float>(j) * stepTexS;
             vt.tex.t = static_cast<float>(i) * stepTexT;

             vt.vector = breitengradpoint;
             vt.color = glm::normalize(vt.vector);

             vc.vector = breitengradpoint;
             vertsTexture.push_back(vt);
             vertsColor.push_back(vc);
        }
    }

    for (i=0; i<_CountPoints*2;i++){
        meridianPoint.x = 0.0f;
        meridianPoint.y = - _Radius;
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

void CSphere::calcNew() {
    // Erstmal NordPol festlegen
    glm::vec3 npol = glm::vec3(0.0,_Radius ,0.0);
    float winkel_laenge = 180.0f / (_CountPoints -1 ) ;
    float winkel_breite = 360.0f / ((_CountPoints  * 2)-1); // ((_CountPoints  * 2) - 1)
    float laengenwinkel = 90.0f - winkel_laenge;
    float breitenwinkel = winkel_breite;

    sVertexTexture vt;   // Structure für Texture Sphere
    sVertexColor   vc;   // Structure für Color Sphere

    glm::vec3 color = glm::vec3(GetColor().x, GetColor().y, GetColor().z);

    // Nordpol ins array für vertexbuffer eintragen
    // structure für Texture Nordpol:
    vt.vector = npol;
    vt.color = glm::normalize(vt.vector);   //color;
    vt.tex   = glm::vec2(0.5,1.0);

    //structure für Color Nordpol
    vc.vector = npol;
    vc.color = color;


    vertsTexture.push_back(vt);
    vertsColor.push_back(vc);

    //--------------------------------------------------------------
    // jetzt den Body : Hilfsvariablen
    //--------------------------------------------------------------
    glm::vec3 laengengrad;
    glm::vec3 breitengrad;

    float texCoordU = 1.0f / ((_CountPoints * 2) -1 ) ;
    float texCoordV = 1.0f / (_CountPoints);
    float texU;
    float texV;

    for (int i = 0; i < _CountPoints - 2; i++) {

        glm::vec2 mPoint;
        calccircle(_Radius, laengenwinkel, mPoint);

        laengenwinkel -= winkel_laenge;
        if ( laengenwinkel < 0.0f )
            laengenwinkel += 360.0f;

        laengengrad.x = mPoint.x;//meridianPoints.at(i).x;
        laengengrad.y = mPoint.y;//meridianPoints.at(i).y;
        laengengrad.z = 0.0;

        // structure für Texture Sphere
        vt.vector = laengengrad;

        // missbrauch von color für normalen vector...
        vt.color = glm::normalize(vt.vector);

        texU = 0.0f;
        texV = (i+1) * texCoordV;
        vt.tex   = glm::vec2(texU,texV);

        //structure für Color
        vc.vector = laengengrad;
        vc.color = color;

        vertsTexture.push_back(vt);
        vertsColor.push_back(vc);

        // ========================================================
        // Jetzt den Breitengrad für jeden längengrad punkt rechnen
        // diesmal CountPoints * 2 -1
        //---------------------------------------------------------
        for (int j = 0; j < _CountPoints * 2 -1;  j++) {//                   -1;  j++) {
            // sehne  :
            glm::vec2 lPoint;

             calccircle(laengengrad.x,breitenwinkel,lPoint);

             breitenwinkel += winkel_breite;

             // Man könnte das ganze auch gleich direkt in das array fürden GPU Mem schreiben
             // .. ist aber so leichter zu lesen
             breitengrad.x = lPoint.x;//latitudePoints.at(j).x;
             breitengrad.y = laengengrad.y;
             breitengrad.z = lPoint.y;//latitudePoints.at(j).y;
             // Texture , diesmal nur u koordinate , v bleibt erstmal
             texU = j * texCoordU;

             vt.vector = breitengrad;
             vt.color = glm::normalize(vt.vector);

             if ( j ==   _CountPoints * 2 - 1  )
                vt.tex = glm::vec2(1.0,1.0);
             else
                vt.tex = glm::vec2(texU,texV);

             //structure für Color Nordpol
             vc.vector = laengengrad;
             vc.color = color;

             vertsTexture.push_back(vt);
             vertsColor.push_back(vc);
        }

        breitenwinkel = winkel_breite;

    }
    // "Südpol"
    vt.vector = glm::vec3(0.0, -(_Radius),0.0) ;
    vt.color = glm::normalize(vt.vector);
    vt.tex = glm::vec2(0.5,0.0);
    //structure für Colorsphere Südpol
    vc.vector = laengengrad;
    vc.color = color;

    vertsTexture.push_back(vt);
    vertsColor.push_back(vc);
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

    for (j = 0; j < _CountPoints; j++) {  // -3

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
