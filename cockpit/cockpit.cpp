#include "cockpit.h"
#include "../defines.h"

Cockpit::Cockpit(glm::mat4 proj)
{
    matrix = proj;
    Mesh->SetProjection(matrix);
    _Rotation = glm::vec3(0.0,0.0,0.0);
    init();
}

void Cockpit::init() {

    transFront = glm::vec3(_Position.x,_Position.y, _Position.z -15);
}

void Cockpit::setMesh(Animate *mesh)
{
    Mesh = mesh;
}
Animate * Cockpit::getCockpitMesch() {
    return Mesh;
}

void Cockpit::InitShader(ShaderType s, GLuint prog) {
    switch(s)
    {
        case ShaderType::COLOR_SHADER       :  Mesh->initShader(s,prog);   break;
        case ShaderType::LIGHT_COLOR_SHADER :  Mesh->initShader(s,prog);   break;
        case ShaderType::LIGHT_SHADER       :  Mesh->initShader(s,prog);   break;
        case ShaderType::TEXTURE_SHADER     :  Mesh->initShader(s,prog);   break;
    }
    Mesh->setActiveShader(s);
}

void Cockpit::setShader(ShaderType st)
{
    Mesh->setActiveShader(st);
}

void Cockpit::Draw(Camera *cam) {
    Mesh->Draw(cam);
}

void Cockpit::Rotate(glm::vec3 rot) {
    _Rotation  = rot;
    Mesh->SetFirstTranslate(true);
    Mesh->Rotate(_Rotation);
   //

}

void Cockpit::Translate(glm::vec3 tran) {
    _Translation = tran;
     Mesh->Translate(glm::vec3(transFront.x + _Translation.x ,transFront.y + _Translation.y, transFront.z + _Translation.z));
}

void Cockpit::setProjectionMatrix(glm::mat4 mat) {
    matrix = mat;
}
void Cockpit::setPosition(Camera * cam) {
    _Position = cam->GetPos();
    transFront = glm::vec3(_Position.x + _Translation.x ,_Position.y + _Translation.y, _Position.z + _Translation.z);
    Mesh->Translate(transFront);
    Mesh->Rotate(_Rotation);
}

glm::vec3 Cockpit::Position() {
    return _Position;
}
