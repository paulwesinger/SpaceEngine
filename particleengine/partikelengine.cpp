
#include "partikelengine.h"


PartikelEngine::PartikelEngine(glm::mat4 pro)
{

    count = 100;

    for (int i = 0; i < count; i++  ) {
        sPartikel p;
        p.emissionPoint = glm::vec3(0,0,-30);

        float y = 0.0 + (static_cast<float>(i) * 0.4) ;
        p.actPos =  glm::vec3(30,y,0);

        float r = 1/300 * static_cast<float>(i);
        float g = 1/300 *static_cast<float>(i*2);
        float b = 1/300 *static_cast<float>(i*3);

        p.color = glm::vec4(r,g,b,0.7);

        p.direction = glm::vec3(0,1,0);     // senkrecht
        p.lifeTime = 5000.0;                //ms
        p.velocity = 1;
        p.textureID = 0;
        p.cube = new CCube(p.actPos,p.color,pro);

        partikel.push_back(p);

    }
}

PartikelEngine::~PartikelEngine(){

    for (int i=0; i < count; i++)
        delete partikel.at(i).cube;

    partikel.clear();
}


void PartikelEngine::Render(Camera *camera) {
    for (int i = 0; i< count; i ++) {
        partikel.at(i).cube->Draw(camera);
    }
}

void PartikelEngine::emit(int id) {

}

void PartikelEngine::destroy(int id) {

}
