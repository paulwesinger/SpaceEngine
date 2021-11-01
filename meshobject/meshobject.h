// ---------------------------------------------------------
// description:
// This class loads a 3DS mesh without normals !!
// it give back a list with this stucture:
// vx vy vz  nx ny nz tx tz -> Vecs, normals, texturecoords
// Normals will be calced during reading the faces^1
// Additional:
// count faces
//---------------------------------------------------------

#ifndef CMESHOBJECT_H
#define CMESHOBJECT_H


#include <SDL2/SDL_image.h>
#include <string>
#include <list>
#include <glm/glm.hpp>

#include "../shaders/shader.h"
#include "../defines.h"
#include "../baseobject/baseobject.h"
#include "../3DLoader/load3ds.h"
#include "../camera/camera.h"
#include "../lights/light.h"

const int GL_DATA_SIZE = 8; // 3*Vector, 3 * NORMALE, 2* Texture
const int FACESIZE = 3;
const int FLOATS_PER_FACE = GL_DATA_SIZE * FACESIZE;  // Needed floats per face
const GLsizei STRIDE = 8;

class CMeshObject : public BaseObject{
public:
    CMeshObject();
    CMeshObject(std::string filename);

    ~CMeshObject();
    virtual void Draw( Camera * cam, GLuint shaderprog);
    bool Load3DSMesh(std::string filename);
    bool LoadOBJMesh(std::string filename);

protected:
    GLsizeiptr arraySize;
    GLsizeiptr indexSize;

private:
    void init();
    bool meshLoaded;
    void init3DSMesh();
    void initOBJMesh();

    void storeInVertexArray(std::vector<GLfloat> &arrayvar, VECTOR v, VECTOR n,TEXTURECOORDS t);

    C3DSLoad * load3DS;
    std::string _Filename;

    std::vector<GLfloat>  meshFloats;
    std::vector<GLshort>  meshIndexes;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    GLint  mv_location;
    GLint           ortho_location;
    GLint           color_location; // Farbe im vertex Shader
    GLint           viewlocation;   // viewmatreix für orhomode
    // Light
    light *  _Light;  // Liste ?

    glm::vec3           _Trans;
    glm::vec3           _Rotate;
    glm::vec3           _Scale;
    glm::vec4           _Color;


};

#endif // CMESHOBJECT_H
