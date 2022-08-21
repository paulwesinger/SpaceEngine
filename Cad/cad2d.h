#ifndef CAD2D_H
#define CAD2D_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


#include "../shaders/shader.h"
//#include "../camera/camera.h"

#include "../defines.h"

using namespace glm;
class BaseCad2D
{
public:
    BaseCad2D();
    BaseCad2D(int resx, int resy);
    void useShader(int type);

    virtual ~BaseCad2D();
    virtual bool Init(int resx,int resy);
    virtual void setPoint0(sPoint p0);
    virtual void setPoint1(sPoint p1);

    virtual bool intersectP0(sPoint p0, sPoint mouse);
    virtual bool intersectP1(sPoint p1, sPoint mouse);

    virtual void Render();
    virtual void OnClick();

    glm::vec2 Pos0();
    glm::vec2 Pos1();
    void setDisablecolor(glm::vec4 disCol);
    void setColor(glm::vec4 col);
    void disable();
    void enable();

    bool IsEnabled();

protected:


    glm::vec4 _Color;
    glm::vec4 _DisableColor;
    glm::vec2 _P0;
    glm::vec2 _P1;

    int _ResX;
    int _ResY;

    GLuint _VAO;
    GLuint _VBO;

    //-----------------
    // Shaders
    //-----------------
    Shader * shader;
    // ints for shader returns
    int vs;
    int fs;
    uint _ColorShader;
    uint _CurrentShader;

    bool _Enabled;

    GLint mv_projectloc;
    GLint uniform_colorloc;
    glm::mat4 projection;

private:
    fileUtil * filestream = nullptr;

};

#endif // CAD2D_H
