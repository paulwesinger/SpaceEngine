#include "cockpit.h"
#include "../defines.h"

Cockpit::Cockpit(glm::mat4 proj,glm::vec3 position)
{
    matrix = proj;
    _Position = position;
    _Rotation = glm::vec3(0.0,0.0,0.0);
   // Mesh->setPolygonMode(GL_POINT); // GL_FILL, GL_LINE
    Mesh = nullptr;
    init();
}

void Cockpit::init() {

    // Hat momentan keine Verwendung , erstmal lassen vielleicht wirds ja noch gebraucht
    transFront = glm::vec3(_Position.x,_Position.y, _Position.z -15);
}

void Cockpit::setMesh(Animate *mesh)
{
    if (mesh != nullptr ) {
        Mesh = mesh;
        Mesh->SetHasAlpha(true);
        Mesh->SetFirstTranslate(true);
    }
}
Animate * Cockpit::getCockpitMesch() {
    return Mesh;
}

bool Cockpit::HasMesh() {
    return (Mesh != nullptr) ? true : false;
}

void Cockpit::InitShader(ShaderType s, GLuint prog) {

    if (Mesh != nullptr) {

        Mesh->initShader(s,prog);
        Mesh->setActiveShader(s);
    }
}

void Cockpit::setShader(ShaderType st)
{
    if ( Mesh != nullptr) {
        Mesh->setActiveShader(st);
    }
}

void Cockpit::Draw(Camera *cam) {
    if ( Mesh != nullptr) {
        Mesh->SetProjection(matrix);
        Mesh->Draw(cam);
    }
}

void Cockpit::Rotate(glm::vec3 rot) {

    _Rotation.x  = -rot.x;
    _Rotation.y  = -rot.y;
    _Rotation.z  = -rot.z;

    if (Mesh != nullptr) {
         Mesh->Rotate(_Rotation);
    }
}

void Cockpit::Steprotate(float step) {
    _StepRotate = step;
}

void Cockpit::Translate(glm::vec3 tran) {
    if (Mesh != nullptr) {
        _Position = tran;
        Mesh->Translate(tran);
    }
}

void Cockpit::setProjectionMatrix(glm::mat4 mat) {
    matrix = mat;
}

void Cockpit::SetDir(glm::vec3 dir) {
    _Dir = dir;
}

void Cockpit::setPosition(Camera * cam) {
    _Position = cam->GetPos();
    Translate(_Position);
}

glm::vec3 Cockpit::Position() {
    return _Position;
}
