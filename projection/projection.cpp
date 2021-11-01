#include "projection.h"
/*
 * File:   projection.cpp
 * Author: paul
 *
 * Created on 14. April 2019, 20:03
 */

#include "projection.h"
#include <glm/gtc/matrix_transform.hpp>

Projection::Projection() {
    // Standards
    _Fov        = glm::radians(33.0f);
    _Aspect     = 16.0f / 10.0f;
    _NearPlane  = -1.0f;  // Darf nicht NULL sein !!!
    _FarPlane   = 10000.0f;
    // Ortho
    _X          = 0.0f;
    _Y          = 0.0f;
    _Width      = 1920.0f;
    _Height     = 1200.0f;

    _Perspective    = glm::perspective(_Fov, _Aspect,_NearPlane, _FarPlane);
    _Ortho          = glm::ortho(_X,_Y,_Width, _Height,  _NearPlane, _FarPlane );
}

Projection::Projection(float fov, float aspect, float near, float far) {

    _Fov        = glm::radians(fov);
    _Aspect     = aspect;
    _NearPlane  = near;
    _FarPlane   = far;
    // Ortho
    _X          = 0.0f;
    _Y          = 0.0f;
    _Width      = 1280.0f;
    _Height     = 720.0f;

    _Perspective    = glm::perspective(_Fov, _Aspect,_NearPlane, _FarPlane);
    _Ortho          = glm::ortho(_X,_Width, _Height, _Y, -1.0f, 1.0f );
}

Projection::Projection(float x, float width, float y, float height, float near, float far) {
    _Fov        = glm::radians(45.0f);
    _Aspect     = 4.0f / 3.0f;
    _NearPlane  = near;
    _FarPlane   = far;
    // Ortho
    _X          = x;
    _Y          = y;
    _Width      = width;
    _Height     = height;

    _Perspective    = glm::perspective(_Fov, _Aspect,_NearPlane, _FarPlane);
    _Ortho          = glm::ortho(_X,_Width, _Height, _Y, -1.0f, 1.0f );
}

Projection::Projection(const Projection& orig) {
}

Projection::~Projection() {
}
// *********************************
// Perspective Stuff
// ---------------------------------
void Projection::SetPerspective(float fov, float aspect, float near, float far) {
    _Fov        = glm::radians(fov);
    _Aspect     = aspect;
    _NearPlane  = near;
    _FarPlane   = far;
    _Perspective = glm::perspective(fov,aspect,near,far);
}

void Projection::SetPerspective(float fov, float aspect) {
    _Fov        = glm::radians(fov);
    _Aspect     = aspect;
    _Perspective = glm::perspective(fov,aspect,_NearPlane,_FarPlane);
}

glm::mat4 & Projection::GetPerspective() {
    return _Perspective;
}

// **********************************
// Ortho Stuff
// ----------------------------------
void Projection::SetOrtho(float x, float width, float y, float height, float near, float far) {
    _NearPlane  = near;
    _FarPlane   = far;
    // Ortho
    _X          = x;
    _Y          = y;
    _Width      = width;
    _Height     = height;

    _Ortho      = glm::ortho(_X,_Width, _Y, _Height );//, _NearPlane, _FarPlane );
}

void Projection::SetOrtho(float x, float width, float y, float height) {
    _X          = x;
    _Y          = y;
    _Width      = width;
    _Height     = height;

    _Ortho      = glm::ortho(_X,_Width, _Y, _Height);//, _NearPlane, _FarPlane );
}

glm::mat4 Projection::GetOrtho() {
    return _Ortho;
}
