#include "cockpit.h"
#include "../defines.h"

Cockpit::Cockpit(glm::mat4 proj)
{
    matrix = proj;
    init();
}

void Cockpit::init() {

    transFront = glm::vec3(_Position.x,_Position.y, _Position.z - 5.0);
/*
    Front = new CCube(glm::vec3(0.0,0.0,0.0),glm::vec4(1.0,0.0,0.0,1.0),matrix);
    //  Front->StepTranslate(transFront); //.x,transFront.y,transFront.z);
    Front->SetHasTextures(true);
    std::vector<std::string> list;
    std::string s = "images/world.png";
    list.push_back(s);
    Front->addTexture(list,"cockpit:init");
    Front->scaleX(2.0);
    Front->scaleY(3.5f);
    Front->scaleZ(1.0);

    Front->SetHasTextures(false);
*/
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
    Mesh->SetProjection(matrix);
    Mesh->SetColor(glm::vec4(1.0,1.0,1.0,0.5));
    Mesh->Translate(glm::vec3(-10,2,20));
    Mesh->Draw(cam);
}

void Cockpit::setProjectionMatrix(glm::mat4 mat) {
    matrix = mat;
}
void Cockpit::setPosition(Camera * cam) {
    _Position = cam->GetPos();
    transFront = glm::vec3(_Position.x,_Position.y, _Position.z - 15.0);
    Mesh->Translate(transFront);//.x,transFront.y,transFront.z);
}

glm::vec3 Cockpit::Position() {
    return _Position;
}
