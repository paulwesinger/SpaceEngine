
#include "partikelengine.h"


PartikelEngine::PartikelEngine(glm::mat4 pro,ShaderType s, int amount)
{
    projection = pro;
    count = amount;
}

PartikelEngine::PartikelEngine(glm::mat4 pro,ShaderType s)
{
    projection = pro;
    count = 100;
}

void PartikelEngine::init(){

    emissiontime = 500;
    currentCount = -1;
    std::vector<std::string> tex;
    std::string sTex = "../SpaceEngine/images/wall.png";
    tex.push_back(sTex);
 //   sTex = "../SpaceEngine/images/wall.png";
 // tex.push_back(sTex);

    for (int i = 0; i < count; i++  ) {
        sPartikel p;
        p.emissionPoint = glm::vec3(10,0,-20);

        float y = 0.0 + (static_cast<float>(i) * 0.4) ;
        p.actPos =  glm::vec3(30+y,y,0);
/*
        float r = 1/300 * static_cast<float>(i);
        float g = 1/300 *static_cast<float>(i*2);
        float b = 1/300 *static_cast<float>(i*3);
*/
        float r = 1.0;
        float g = 1.0;
        float b = 0.4;

        p.color = glm::vec4(r,g,b,0.7);

        p.direction = glm::vec3(0,1,0);     // senkrecht
        p.lifeTime = 5000.0;                //ms
        p.UsedTime = 0;
        p.velocity = 1.0f;
        p.weight   = 5.0f;
        p.textureID = 0;
        p.render    = false;

        p.cube = new CCube(p.actPos,p.color,projection);
     //   p.cube->scaleX(0.2);
     //   p.cube->scaleY(2.0);
     //   p.cube->scaleZ(0.2);
        //p.cube->translateX(1.0);
        //p.cube->StepTranslate(glm::vec3(0,p.emissionPoint.y  + static_cast<float>(i),0));
        p.cube->Translate(p.actPos);


        p.cube->initShader(ShaderType::TEXTURE_SHADER,perspectiveTextureShader);
        p.cube->initShader(ShaderType::COLOR_SHADER,perspectiveTextureShader);
        p.cube->initShader(ShaderType::LIGHT_SHADER,lightshader);
        p.cube->initShader(ShaderType::LIGHT_TEXTURE_SHADER,lighttextureshader);
        p.cube->initShader(ShaderType::LIGHT_COLOR_SHADER,lighttextureshader);
        p.cube->initShader(ShaderType::GLASS_SHADER,glasshader);

        p.cube->setActiveShader(ShaderType::TEXTURE_SHADER);
        p.cube->addTexture(tex,"PartikelEngine");
        partikel.push_back(p);
    }
}

void PartikelEngine::setShader(ShaderType s, GLuint prog) {
   switch (s) {
        case TEXTURE_SHADER         :  perspectiveTextureShader = prog; break;
        case COLOR_SHADER           :  perspectiveTextureShader = prog; break;
        case LIGHT_SHADER           :  lightshader = prog; break;
        case LIGHT_TEXTURE_SHADER   :  lighttextureshader = prog; break;
        case LIGHT_COLOR_SHADER     :  lighttextureshader = prog; break;
        case GLASS_SHADER           :  glasshader = prog; break;
   default:
       currentShader = prog;
   }
   currentShader = prog;
}

PartikelEngine::~PartikelEngine(){

    for (int i=0; i < count; i++)
        delete partikel.at(i).cube;

    partikel.clear();
}

void PartikelEngine::setEmissionTime(uint ms) {
    emissiontime = ms;
}

void PartikelEngine::Render(Camera *camera,Uint32 el) {

    elapsed += el ;

    if (elapsed >= emissiontime) {
        currentCount ++;
        elapsed = 0;
    }

    if (currentCount > count -1)
        currentCount = -1;

    if (currentCount > -1 ) {
//        for (int i = 0; i <= currentCount; i++)  {
//            emit(i,camera);

//        }
    }
}

void PartikelEngine::emit(int id, Camera * camera) {
 //   partikel.at(id).cube->StepTranslate(glm::vec3(0.0,0.4,0));
    partikel.at(id).cube->Draw(camera);
}

void PartikelEngine::destroy(int id) {

}
