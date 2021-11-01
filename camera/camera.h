#ifndef CAMERA_H
#define CAMERA_H
/*
 * File:   Camera.h
 * Author: paul
 *
 * Created on 31. Dezember 2018, 20:50
 */
#include <cstdio>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>

//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//#include <glm/mat4x4.hpp>

#include "../defines.h"

/*
template <typename T>
static inline Tmat4<T> lookat(const vecN<T,3>& eye, const vecN<T,3>& center, const vecN<T,3>& up)
{
    const Tvec3<T> f = normalize(center - eye);
    const Tvec3<T> upN = normalize(up);
    const Tvec3<T> s = cross(f, upN);
    const Tvec3<T> u = cross(s, f);
    const Tmat4<T> M = Tmat4<T>(Tvec4<T>(s[0], u[0], -f[0], T(0)),
                                Tvec4<T>(s[1], u[1], -f[1], T(0)),
                                Tvec4<T>(s[2], u[2], -f[2], T(0)),
                                Tvec4<T>(T(0), T(0), T(0), T(1)));

    return M * translate<T>(-eye);
}
*/
class Camera {
public:
    Camera();
    Camera(const Camera& orig);
    virtual ~Camera();
  //  void SetTransPosZ( float t);
    void SetDir( glm::vec3 d);
    void SetPYR( glm::vec3 pyr);
    void SetView(glm::mat4 v);
    void SetPos(glm::vec3 p);
    void SetSpeed(float s);

    glm::vec3 GetPos();
    glm::vec3 GetDir();
    glm::vec3 GetPYR();
    // Origins ( Identity )
    glm::vec3 GetOrgPos();
    glm::vec3 GetOrgDir();
    glm::vec3 GetOrgPYR();

    glm::mat4 GetView();
    float GetSpeed();
   // void HandleEvent (uint e, uint etime);

    // Denke mal löschen
    void SetMotions(uint motx, uint moty,MOUSE m,uint elapsed);

    // ----------------------------------------------------------------
    // Pitch und Yaw sind auf + - 90° limitiert.
    // Vergleichbar mit Kopf drehen nach links,rechts, oben und unten
    // Körper (camera Up und Right Vektor sind trotzdem noch gleich...)
    // ----------------------------------------------------------------
    void PitchEyeDown( uint elapsed);
    void PitchEyeUp(uint elapsed);
    void YawEyeLeft(uint elapsed);
    void YawEyeRight(uint elapsed);

    // -----------------------------------------------------------------------
    // YawEyeLeft,YawEyeRight, PitchEyeDown,PitchEyeUP drehen die ganze kamera
    // und damit auch die Blickrichtung
    //------------------------------------------------------------------------
    // y- Achse
    void YawCameraLeft(uint elapsed);
    void YawCameraRight(uint elapsed);
    // x -Achse
    void PitchCameraDown(uint elapsed);
    void PitchCameraUp(uint elapsed);
    // Z- Achse
    void RollCameraLeft(uint elapsed);
    void RollCameraRight(uint elapsed);

    // -----------------------------------------------------------------------
    // MoveForward,MoveBackward,MoveRight,MoveLeft : Schritt nach vorne,
    // Rückwärts, Links, Rechts.
    // und damit auch die Blickrichtung
    //------------------------------------------------------------------------
    void MoveForward(uint elapsed);
    void MoveBackward(uint elapsed);
    void MoveRight(uint elapsed);
    void MoveLeft(uint elapsed);

    void UpdateCamera();
private:

    glm::mat4 _View;

    glm::vec3 _Pos;
    glm::vec3 _Dir;
    glm::vec3 _Up;
    // Origins
    glm::vec3 _OrgPos;
    glm::vec3 _OrgDir;
    glm::vec3 _OrgUp;
    glm::vec3 _OrgRight;

    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 Pitch;

    float _YawEye, _YawCamera;
    float _PitchEye, _PitchCamera;
    float _RollEye, _RollCamera;
    float _ElapsedTime;
    float _MouseSens;
    float _Speed;
};

#endif // CAMERA_H
