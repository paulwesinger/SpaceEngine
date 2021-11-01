#ifndef BASE2D_H
#define BASE2D_H

#include <cstdio>
#include <string>
#include <GL/glew.h>
//#include <glad.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
//#include <glm/gtx/detail/type_mat4x4.hpp>

#include "../shaders/shader.h"
//#include "../camera/camera.h"

#include "../defines.h"

using namespace glm;

class Base2D {
public:
    Base2D(int resx, int resy);
    Base2D(int resx, int resy,std::string path);
    Base2D(const Base2D& orig);
    virtual ~Base2D();
    bool Init(int resx,int resy);
    void setImage(std::string path);
    void useShader(int type);

    virtual void setWidth( int w);
    virtual void setHeight( int h);
    virtual void setSize( int w, int h);
    virtual void setPos(int x, int y);
    virtual void setColor(glm::vec4 col);

    virtual void disable();
    virtual void enable();

    virtual int Height();
    virtual int Width();

    bool IsEnabled();
    sPoint Pos();
    void setDisablecolor(glm::vec4 disCol);

    glm::vec4 color();
    virtual bool  intersect(int x, int y);

    virtual void Render();
    virtual void OnClick();

protected:


    glm::vec4 _Color;
    glm::vec4 _DisableColor;

    sPoint _Pos;
    sSize _Size;

    bool _Enable;

private:

    int _ResX;
    int _ResY;

    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;
    //-----------------
    // Shaders
    //-----------------
    Shader * shader;
    // ints for shader returns
    int vs;
    int fs;
    int _TextureShader;  // the linked shaders
    int _ColorShader;
    int _CurrentShader;
    std::string _ImagePath;


    GLint mv_projectloc;
    GLint uniform_colorloc;
    glm::mat4 projection;
    unsigned int texture;

};

#endif // BASE2D_H
