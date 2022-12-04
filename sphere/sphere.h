#ifndef CSPHERE_H
#define CSPHERE_H

/*
 * File:   CSphere.h
 * Author: paul
 *
 * Created on 27. Oktober 2019, 20:03
 */

#include <cstdio>

//#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>

#include "../shaders/shader.h"
#include "../baseobject/baseobject.h"
#include "../camera/camera.h"
#include "../defines.h"
#include "../Animate/animate.h"




class CSphere  : public Animate{    //BaseObject {
public:
    CSphere();
    CSphere(int points);
    CSphere(int points, GLfloat rad);

    CSphere(const CSphere& orig);

    CSphere(glm::vec3 origin, glm::mat4 pro);
    CSphere(glm::vec3 origin, glm::mat4 pro, int points);
    CSphere(glm::vec3 origin, glm::mat4 pro, int points, GLfloat rad,Shader * shad);

    CSphere(vec3 origin , vec4 color, glm::mat4 pro);
    CSphere(vec3 origin , vec4 color, glm::mat4 pro, int points);
    CSphere(vec3 origin , vec4 color, glm::mat4 pro, int points, GLfloat rad, Shader * shad);
    ~CSphere();
    virtual void Draw(Camera * cam );//, GLuint &shaderprog);
    virtual void SetColor(vec4 color);

    void setCountMeshPoints(int c);
    void setRadius(GLfloat rad);

    void setUp();

protected:
    // einen Vektor für den GPU-Mem vorbereiten
    void Add2GPU(float*v, int &index, GLfloat vx, GLfloat vy, GLfloat vz);
    void Add2GPU(float*v, int &index,glm::vec3 vec);
    void Add2GPU(float*v, int &index,glm::vec2 vec);

private:
    // Buffers for Opengl

    GLuint  _Vao, _VertexBuffer,_Ebo_npol, _Ebo_spol;
    GLuint _BodyPoints;
    std::vector<GLushort> body;
    std::vector<GLushort> northPol;
    std::vector<GLushort> southPol;

    GLint   color_location;

    Shader * shader;
    GLfloat _Radius;
    int _CountPoints;


    // Neue Version für Vertex calculation:
    //std::vector<sVertexTexture> vertsTexture;
    std::vector<sVertexNormals> vertsNormals;
    std::vector<sVertexColor> vertsColor;
    void calcStrip();
};


#endif // CSPHERE_H
