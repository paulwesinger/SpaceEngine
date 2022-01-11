#include "camera.h"
/*
 * File:   Camera.cpp
 * Author: paul
 *
 * Created on 31. Dezember 2018, 20:50
 */
//#include <glad.h>


#include<GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>  ///rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../vecmath/vecmath.h"


Camera::Camera() {
    _Pos = glm::vec3( 0.0,2.0, 10.0);
    _Dir = glm::vec3( 0.0, 0.0,1.0);
    _Up = glm::vec3( 0.0,1.0,0.0);

    Up    = glm::vec3(0.0,1.0,0.0);
    Right = glm::vec3(1.0,0.0,0.0);
    Pitch = glm::vec3(0.0,0.0,1.0);

    _OrgPos = _Pos;
    _OrgDir = _Dir;
    _OrgUp = _Up;
    _OrgRight = glm::vec3(1.0,0.0,0.0);

    _YawCamera        = 270.0f;
    _YawEye           = 0.0f;
    _PitchCamera      = 0.0f;
    _PitchEye         = 0.0f;
    _RollEye          = 0.0f;
    _RollCamera       = 0.0f;
    _Speed      = 1.0f;
    _MouseSens  = 0.2;

    _View = glm::lookAt( _Pos, _Dir, _Up );

}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

// -----------------------------------
// public Functions
// -----------------------------------

glm::mat4 Camera::GetView() {
    return _View;
}

void Camera::UpdateCamera() {
    _View = glm::lookAt(_Pos,_Pos + _Dir,_Up);
}

// Winkel wird errechnet : _Speed * elapsed / 1000

void Camera::PitchEyeDown(uint elapsed) {
    /*

   float vel = _Speed * ((float) elapsed /1000) ;
    _Pitch -= vel;

    if (_Pitch < 0.0f)
        _Pitch += 360.0f;

    //float radians = glm::radians(_Pitch);

     //glm::vec3 newPitch = glm::rotat    (_OrgDir,_Pitch);
    glm::vec3 newPitch = glm::rotateX(_OrgDir,_Pitch);
    _Dir = glm::normalize(newPitch);
    newPitch = glm::normalize(_Pos - newPitch);

    glm::vec3 right  = glm::normalize(glm::cross(_OrgUp,newPitch));
    _Up = glm::normalize(glm::cross(newPitch,right));

    UpdateCamera();
    */
}
void Camera::PitchEyeUp(uint elapsed){

    /*
    float vel = _Speed * ((float)elapsed / 1000);
    _Pitch += vel;
    if ( _Pitch >= 360.0f  )
        _Pitch -=  360.0f;

    glm::vec3 newDir = glm::rotateX(_OrgDir,_Pitch);  // Vector drehen
    _Dir = glm::normalize(newDir);
    newDir = glm::normalize(_Pos - newDir);

    glm::vec3 right  = glm::normalize(glm::cross(_OrgUp,newDir));
    //float radians = glm::radians(_Pitch);
    _Up = glm::normalize(glm::cross(newDir,right));

    UpdateCamera();
    */
}
void Camera::YawEyeLeft(uint elapsed) {
    /*
    float vel = _Speed * ((float)elapsed / 1000);
    _Yaw += vel;
    if ( _Yaw >= 360.0f  )
        _Yaw -=  360.0f;
    glm::vec3 newDir = glm::rotateY(_OrgDir,_Yaw);
    _Dir = glm::normalize(newDir);
  //  _Up = glm::normalize(_Up) ;
    UpdateCamera();
    */
}
void Camera::YawEyeRight(uint elapsed){
/*
    float vel = _Speed * ((float)elapsed / 1000) ;
    _Yaw -= vel;
    if ( _Yaw <= 0.0f  )
        _Yaw +=  360.0f;

    glm::vec3 newDir = glm::rotateY(_OrgDir,_Yaw);
    _Dir = glm::normalize(newDir);
    //_Up = glm::normalize( _Up);
    UpdateCamera();
    */
}

void Camera::SetSpeed(float s) {
    _Speed = s;
}

float Camera::GetSpeed() {
    return _Speed;
}
// --------------------------------------------------------------
// "Schritte Links,Rechts, Vor und Zurück
// --------------------------------------------------------------
void Camera::MoveForward(uint elapsed) {
    float vel = _Speed * ((float)elapsed / 100);
    _Pos += _Dir * vel;
    _View = glm::lookAt(_Pos,_Pos + _Dir,Up );
}

void Camera::MoveBackward(uint elapsed) {
    float vel =  _Speed * ((float)elapsed / 100);

    _Pos -= _Dir * vel;
    _View = glm::lookAt(_Pos,_Pos + _Dir,Up );
}

void Camera::MoveLeft(uint elapsed) {
    float vel =  _Speed * ((float)elapsed / 100);
    _Pos += Right * vel;
    _View = glm::lookAt(_Pos,_Pos + _Dir,Up );
}

void Camera::MoveRight(uint elapsed) {
    float vel =  _Speed * ((float)elapsed / 100);
    _Pos -= Right * vel;
    _View = glm::lookAt(_Pos,_Pos + _Dir,Up );
}

// -----------------------------------------------------
// Camera rotations   1 radiant = 0,0174532925199433
// -----------------------------------------------------
void Camera::YawCameraLeft(uint elapsed) {

    float vel = _Speed * elapsed / 100;
    _YawCamera -= vel;
    checkdegree(_YawCamera);
    _Dir.x = cos(glm::radians(_YawCamera)) * cos(glm::radians(_PitchCamera));
    _Dir.y = sin(glm::radians(_PitchCamera));
    _Dir.z = sin(glm::radians(_YawCamera)) * cos(glm::radians(_PitchCamera));
    _Dir = glm::normalize(_Dir);
    UpdateCamera();
}
void Camera::YawCameraRight(uint elapsed) {
    float vel = _Speed * elapsed / 100;
    _YawCamera += vel;
    checkdegree(_YawCamera);
    _Dir.x = cos(glm::radians(_YawCamera)) * cos(glm::radians(_PitchCamera));
    _Dir.y = sin(glm::radians(_PitchCamera));
    _Dir.z = sin(glm::radians(_YawCamera)) * cos(glm::radians(_PitchCamera));
    _Dir = glm::normalize(_Dir);
    UpdateCamera();
}

void Camera::PitchCameraUp(uint elapsed) {

    float vel = _Speed * elapsed / 100;
    // Winkel;
    _PitchCamera += vel;
    checkdegree(_PitchCamera);

    _Dir.x = cos(glm::radians(_YawCamera)) * cos(glm::radians(_PitchCamera));
    _Dir.y = sin(glm::radians(_PitchCamera));
    _Dir.z = sin(glm::radians(_YawCamera)) * cos(glm::radians(_PitchCamera));
    _Dir = glm::normalize(_Dir);
    UpdateCamera();
}
void Camera::PitchCameraDown(uint elapsed) {

    float vel = _Speed * elapsed / 100;
    // Winkel;
    _PitchCamera -= vel;
    checkdegree(_PitchCamera);
    _Dir.x = cos(glm::radians(_YawCamera)) * cos(glm::radians(_PitchCamera));
    _Dir.y = sin(glm::radians(_PitchCamera));
    _Dir.z = sin(glm::radians(_YawCamera)) * cos(glm::radians(_PitchCamera));
    _Dir = glm::normalize(_Dir);
    UpdateCamera();
}

float Camera::YawCameraDEG() {
    return _YawCamera;
}

float Camera::PitchCameraDEG() {
    return _PitchCamera;
}

float Camera::RollCameraDEG() {
    return _RollCamera;
}

glm::vec3 Camera::MoveDirectionDEG(){
    return glm::vec3(_PitchCamera, _YawCamera, _RollCamera);
}

void Camera::SetMotions(uint motx,uint moty,MOUSE m,uint elapsed) {

    logwarn("_MOTIONX  " + IntToString(motx ),"Camera::SetMotions");
    logwarn("_MOTIONY  " + IntToString(moty ),"Camera::SetMotions");

    float velocity = _Speed * elapsed / 10;
    logwarn("Velocity = " + FloatToString(velocity),"Camera");

    /*
     switch (motx){

        case MOUSE_Move_Right: {
            _Yaw += velocity ;
            if ( _Yaw > 359.0f )
                _Yaw = _Yaw - 360.0f ;
            logwarn("_Yaw +++ " + FloatToString(_Yaw ),"Camera::SetMotions");

            UpdateCamera();
            break;
        }
        case MOUSE_Move_Left: {
            _Yaw -= velocity;
            if ( _Yaw < 0.0f )
                _Yaw = 360.0f - _Yaw ;
            logwarn("_Yaw ---- " + FloatToString(_Yaw),"Camera::SetMotions");
            UpdateCamera();
            break;
        }
    }

    switch ( moty) {
        case MOUSE_Move_Up : {
            _Pitch += velocity;
            if (_Pitch > 360.0f)
                _Pitch = _Pitch - 360.0f;
            logwarn("_Pitch +++ " + FloatToString(_Pitch),"Camera::SetMotions");
            UpdateCamera();
            break;
        }
        case MOUSE_Move_Down: {
            _Pitch -= velocity;
            if ( _Pitch < 0.0 )
                _Pitch = 360.0f - _Pitch;
            logwarn("_Pitch ----" + FloatToString(_Pitch),"Camera::SetMotions");
            UpdateCamera();
            break;
        }
    }
    */
    UpdateCamera();
}



void Camera::SetDir(glm::vec3 d ) { _Dir = d; }

void Camera::SetPYR(glm::vec3 pyr){ _Up = pyr; }

void Camera::SetPos(glm::vec3 p) { _Pos = p;  }

void Camera::SetView(glm::mat4 v) { _View = v; }

glm::vec3 Camera::GetPos()  { return _Pos; }
glm::vec3 Camera::GetDir()  { return _Dir; }
glm::vec3 Camera::GetPYR()  { return _Up; }

glm::vec3 Camera::GetOrgPos()  { return _OrgPos; }
glm::vec3 Camera::GetOrgDir()  { return _OrgDir; }
glm::vec3 Camera::GetOrgPYR()  { return _OrgUp; }

