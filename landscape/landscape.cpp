
#include <GL/glew.h>
//#include <GL/gl.h>


#include "landscape.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../imageloader/loadimage.h"
#include "../vecmath/vecmath.h"
#include "../defaults.h"

LandScape::LandScape()
    :BaseObject() {
    _RasterX = TERRAIN::RASTER_X;
    _RasterZ = TERRAIN::RASTER_Z;
    _PatchX = TERRAIN::PATCH_X;
    _PatchZ = TERRAIN::PATCH_Z;
}
LandScape::LandScape(float rasterx, float rastery)
    : BaseObject() {
    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = TERRAIN::PATCH_X;
    _PatchZ = TERRAIN::PATCH_Z;
}

LandScape::LandScape(int patchx, int patchy, float rasterx, float rastery)
    :BaseObject(){
    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = patchx;
    _PatchZ = patchy;
}

LandScape::LandScape(int patchx, int patchy, float rasterx, float rastery, vec3 color)
    :BaseObject(BASE::ZERO_VEC3,BASE::ZERO_VEC3,BASE::ZERO_VEC3, glm::vec4(color,1.0)){

    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = patchx;
    _PatchZ = patchy;
}

LandScape::~LandScape(){
    glDeleteVertexArrays(1, &_Vao);
    glDeleteBuffers(1, &_Vbo);
    glDeleteBuffers(1, &_Ebo);
    glDeleteProgram(perspectiveColorShader);
    glDeleteProgram(perspectiveTextureShader);
}

void LandScape::setPatchX(int px) { _PatchX = px; }
void LandScape::setPatchZ(int pz) { _PatchZ = pz; }
void LandScape::setRasterZ(float rz) { _RasterZ = rz; }
void LandScape::setRasterX(float rx) { _RasterX = rx; }

void LandScape::Draw(Camera *cam) {

    glUseProgram( currentShader);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    // Locate uniforms in shader
    mv_location = glGetUniformLocation(currentShader, "mv_matrix");
    int projectionloc = glGetUniformLocation(currentShader,"projection");
    int viewloc = glGetUniformLocation(currentShader,"view");
    int hasTextureloc  = glGetUniformLocation(currentShader,"hasTexture");

    // Model  Lightning
    int modellocation = glGetUniformLocation(currentShader,"model");
    int lightlocation = glGetUniformLocation(currentShader,"lightpos");
    int lightcolorlocation = glGetUniformLocation(currentShader,"lightcolor");
    int useTex2Location = glGetUniformLocation(currentShader,"useTexture_2");
    int useBlinnLocation = glGetUniformLocation(currentShader,"blinn");

    glUniform1i(hasTextureloc,_HasTextures);
    glUniform1i(useBlinnLocation,_UseBlinn);
    glUniform4f(color_location,_Color.r,_Color.g, _Color.b, _Color.a);

    if (_HasTextures) {
        if (_CountTextures > 1)
           glUniform1i(useTex2Location,true);
        else
           glUniform1i(useTex2Location,false);
    }

    //Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model= glm::mat4(1.0f);

    if (HasAnimation() ) {
        if (  GetFirstTranslate() ) {

            Model = glm::translate(Model,GetTranslate());
            Model = glm::rotate(Model, radians(GetRotate().x),vec3(1.0,0.0,0.0));
            Model = glm::rotate(Model, radians(GetRotate().y),vec3(0.0,1.0,0.0));
            Model = glm::rotate(Model, radians(GetRotate().z),vec3(0.0,0.0,1.0));
        }
        else {
            Model = glm::rotate(Model, radians(GetRotate().x),vec3(1.0,0.0,0.0));
            Model = glm::rotate(Model, radians(GetRotate().y),vec3(0.0,1.0,0.0));
            Model = glm::rotate(Model, radians(GetRotate().z),vec3(0.0,0.0,1.0));
            Model = glm::translate(Model,GetTranslate());
        }

    }
      // -----------------------------------------
    // Lightning
    // -----------------------------------------
    glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(Model));

    if ( _Light != nullptr) {
        glm::vec3 c =   _Light->getColor();
        glm::vec3 p =   _Light->getPos();
        glUniform3f(lightlocation,p.x,p.y,p.z);
        glUniform3f(lightcolorlocation,c.x,c.y,c.z);
    }
    else {
        glm::vec3 lightpos = vec3(-10.0,2.0,-5.0);
        glm::vec3 lightcolor = glm::vec3( 0.0,1.0,0.0);
        glUniform3f(lightlocation,lightpos.x,lightpos.y,lightpos.z);
        glUniform3f(lightcolorlocation,lightcolor.x,lightcolor.y,lightcolor.z);
    }

    glFrontFace(GL_CCW);

    glUniformMatrix4fv(projectionloc,1,GL_FALSE,glm::value_ptr(GetProjection()));
    glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam->GetView()));

    if (_HasTextures) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_Textures[0]);
        if (_CountTextures > 1 ) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, _Textures[1]);
        }
    }
    glBindVertexArray(_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_Ebo);

    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(0);
}

float LandScape::genrateHeight(float ypos, float max, float min) {
    float hlp = max + abs(min);
    float fachlp = std::min( (hlp / static_cast<float>(rand() % (int)hlp)),max);
    return  ypos +  fachlp ;
}

void LandScape::setUp() {

    float y = -10.0f;
    //sVertexTexture vt;
    sVertexNormals vn;

    //------------------------------------------
    // erstmal ein paar setups für die geometrie
    // landscape im mittelpunkt definieren
    //------------------------------------------

    initOk = _PatchX > 0 && _PatchZ > 0 && _RasterX > 0.0f && _RasterZ > 0.0f;
    if (  initOk ) {

        float sizeX = (static_cast<float>(_PatchX) * _RasterX) / 2 ;
        float sizeZ = (static_cast<float>(_PatchZ) * _RasterZ) / 2 ;

        float startX = -sizeX; //Linke seite negative
        float startZ = -sizeZ;

        float texU = 1.0f / _RasterX;
        float texV = 1.0f / _RasterZ;

        float maxY = 9.0f;
        float minY = -10.0f;
        for (int j = 0; j < _PatchZ; j++ ) {
             for (int i = 0; i < _PatchX; i++) {

                // ------------------------------------------------------
                // Vektoren
                // ------------------------------------------------------
                vn.vector.x = startX +(static_cast<float>(i) * _RasterX);
                vn.vector.y = genrateHeight(y,maxY,minY); // hier generator für höhe einbauen
                vn.vector.z = startZ + (static_cast<float>(j) * _RasterZ);

                // -------------------------------------------------------
                // Normals
                // -------------------------------------------------------
                vn.normals = glm::normalize(vn.vector);

                // -------------------------------------------------------
                // Color  (Normals)
                // -------------------------------------------------------
                vn.color.r = 0.0f;
                vn.color.g = 1.0f;
                vn.color.b = 0.0f;

                //--------------------------------------------------------
                //Texture coordinaten - nur für texshader landscape
                //--------------------------------------------------------
                vn.tex.x = (static_cast<float>(i) * texU);
                vn.tex.y = (static_cast<float>(j) * texV);

                vertsNormal.push_back(vn);
            }
        }
    }
    else
        logwarn("setup fail landscape will not be shown ","Landscape");
}

bool LandScape::init(){

    loginfo("Create Landscape","Landscape::init");

    _CountTextures = 0;
    setUp();

    loginfo("size of Landscape " + IntToString(_PatchX) + " x "+ IntToString(_PatchZ) ,"Landscape::init");

    if ( initOk) {

    glGenVertexArrays(1,&_Vao);
    // Vertex Buffer
    glGenBuffers(1,&_Vbo);
    glGenBuffers(1,&_Ebo);

    glBindVertexArray(_Vao);

    glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 vertsNormal.size() * sizeof(sVertexNormals),
                 &vertsNormal[0],
                 GL_DYNAMIC_DRAW);
    // Vertex
    glVertexAttribPointer(0,3,GL_FLOAT, GL_TRUE, 11 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //Normale
    glVertexAttribPointer(1,3,GL_FLOAT, GL_TRUE, 11 * sizeof(float),(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Color
    glVertexAttribPointer(2,3,GL_FLOAT, GL_TRUE, 11 * sizeof(float),(void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Texture
    glVertexAttribPointer(3,2,GL_FLOAT,GL_TRUE, 11 * sizeof(float), (void*)(9 *sizeof(float)));
    glEnableVertexAttribArray(3);

    // -----------------------------------------
    // generate indices
    // Sphere body
    //------------------------------------------
    GLushort x = 0;
    GLushort patchx = static_cast<GLushort>(_PatchX) ;
    GLushort hlp = static_cast<GLushort>(_PatchZ);
    ushort i, j;

    for (j = 0; j < _PatchX-1; j++) {  // -3

        for (i= 0; i < hlp-1; i++){
            indices.push_back(i +  x);
            indices.push_back(i+x+patchx);
        }
        x += patchx;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(GLushort),
                 &indices[0],
                GL_DYNAMIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    loginfo("Landscape ........ Done","Landscape::init");
    }
    else
        logwarn("Landscape  wurde nicht initialisiert !!","Landscape::init");

    return ( initOk);
}
