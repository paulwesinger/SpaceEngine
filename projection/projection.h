#ifndef PROJECTION_H
#define PROJECTION_H

/*
 * File:   projection.h
 * Author: paul
 *
 * Created on 14. April 2019, 20:03
 */

//#include <glm/glm.hpp>


#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec3.hpp>

class Projection {
public:
    Projection();
    Projection(float fov,float aspect, float near, float far);                      // Constructor Perspective
    Projection(float x,float width, float y, float height,float near, float far);   //Constructor Ortho
    Projection(const Projection& orig);
    virtual ~Projection();

    void SetPerspective(float fov,float aspect, float near, float far);
    void SetPerspective(float fov,float aspect);
    glm::mat4 & GetPerspective();

    void SetOrtho(float x,float width, float y, float height,float near, float far);
    void SetOrtho(float x,float width, float y, float height);
    glm::mat4 GetOrtho();
private:
    // ***********************
    // Members
    // -----------------------

    // The two MAtrices
    glm::mat4 _Perspective;
    glm::mat4 _Ortho;

    // Members for Field of view,Aspect ratio, near and z plane
    // perspective
    float _Fov;
    float _Aspect;
    float _NearPlane;
    float _FarPlane;
    //ortho
    float _X;
    float _Y;
    float _Width;
    float _Height;
};
#endif // PROJECTION_H
