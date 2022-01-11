#include "cockpit.h"
#include "../defines.h"

Cockpit::Cockpit(glm::mat4 proj,glm::vec3 position)
{
    matrix = proj;
    _Position = position;
    _Rotation = glm::vec3(0.0,0.0,0.0);
   // Mesh->setPolygonMode(GL_POINT); // GL_FILL, GL_LINE
    init();
}

void Cockpit::init() {

    transFront = glm::vec3(_Position.x,_Position.y, _Position.z -15);
}

void Cockpit::setMesh(Animate *mesh)
{
    Mesh = mesh;
    Mesh->SetColor(glm::vec4(1.0,1.0,1.0,0.4));
 //   Mesh->translate(_Position.x+transFront.x,_Position.y+transFront.y,_Position.z+transFront.z);
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
    Mesh->SetProjection(matrix);
    Mesh->Draw(cam);
}

void Cockpit::Rotate(glm::vec3 rot) {
    _Rotation.x  = rot.x;
    _Rotation.y  = -rot.y;
    _Rotation.z  = -rot.z;

    Mesh->SetFirstTranslate(true);
    Mesh->Rotate(_Rotation);

}

void Cockpit::Steprotate(float step) {
    _StepRotate = step;
}

void Cockpit::Translate(glm::vec3 tran) {
    //_Translation = tran;
    //transFront = glm::vec3(((_Position.x) ) ,((_Position.y)), ((_Position.z)));
    Mesh->Translate(_Position);
}

void Cockpit::setProjectionMatrix(glm::mat4 mat) {
    matrix = mat;
}

void Cockpit::SetDir(glm::vec3 dir) {
    _Dir = dir;
}

void Cockpit::setPosition(Camera * cam) {
    _Position = cam->GetPos();
}

glm::vec3 Cockpit::Position() {
    return _Position;
}
