#ifndef CAD2D_H
#define CAD2D_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#include "../shaders/shader.h"
#include "../camera/camera.h"

#include "../defines.h"
#include "../Base/base.h"


const int MAX_POINTS  = 100;


using namespace glm;
class BaseCad2D : public Base
{
public:
    BaseCad2D();
    BaseCad2D(int resx, int resy,glm::mat4 perspektive,glm::mat4 ortho);
    virtual ~BaseCad2D();

    virtual void setPoint0(sPoint p0);
    virtual void setPoint1(sPoint p1);

    virtual void addPoint(Point p);
    virtual void addPoint(int x, int y);

    virtual bool intersectP0(sPoint p0, sPoint mouse);
    virtual bool intersectP1(sPoint p1, sPoint mouse);

    virtual void Render() override;
    virtual void OnClick();

    glm::vec2 Pos0();
    glm::vec2 Pos1();

    void setDisablecolor(glm::vec4 disCol);
    void setColor(glm::vec4 col);
    void disable();
    void enable();
    void useShader(GLuint s);

    bool Init(int resx,int resy);
    bool IsEnabled();

protected:


    glm::vec4 _Color;
    glm::vec4 _DisableColor;
    glm::vec2 _P0;
    glm::vec2 _P1;

    std::vector<Point> _Points;

    int _ResX;
    int _ResY;

    GLuint _VAO;
    GLuint _VBO;

    //-----------------
    // Shaders
    //-----------------
    Shader * shader;
    glm::mat4 matPerspective;
    glm::mat4 matOrtho;
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
