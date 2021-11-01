#ifndef LANDSCAPE_H
#define LANDSCAPE_H



#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>


#include "../baseobject/baseobject.h"
#include "../defines.h"
#include "../camera/camera.h"
#include "../lights/light.h"
#include "../shaders/shader.h"

using namespace glm;


/*
 * Beschreibung:
 * Auflösung  des Tile: 32x32
 * Siehe auch Buch Gems 2 !!
 *
*/


class LandScape : public BaseObject
{
public:
    LandScape();
    LandScape(float rasterx, float rastey);
    LandScape(int patchx, int patchy, float rasterx, float rastey);
    LandScape(int patchx, int patchy, float rasterx, float rastey, vec3 color);
    ~LandScape();


    void Draw(Camera *cam);
    // Object Loading:
    // Patches resolution
    void setPatchX(int px);
    void setPatchZ(int pz);
    // Raster margin
    void setRasterX(float rx);
    void setRasterZ(float rz);

    bool init();

protected:
    uint _Vao, _Vbo,_Ebo;
    GLint           mv_location;
    GLint           ortho_location;
    GLint           color_location; // Farbe im vertex Shader

    vec3           _Trans;
    vec3           _Rotate;
    vec3           _Scale;
    vec4           _Color;
    Shader *       _Shader;

    float genrateHeight(float ypos, float max, float min);

private:
    std::vector<sVertexTexture>  vertsTex;
    std::vector<sVertexColor> vertsCol;

    std::vector<ushort> indices;

    float _RasterX;
    float _RasterZ;

    int _PatchX;
    int _PatchZ;

    void setUp();

    bool initOk;


};

#endif // LANDSCAPE_H
