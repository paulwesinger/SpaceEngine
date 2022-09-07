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
#include "../Base/base.h"
//#include "../Cad/cad2d.h"

#include "../defines.h"

using namespace glm;

class Base2D  : public Base {
public:
    Base2D(int resx, int resy);
    Base2D(int resx, int resy,std::string path);
    Base2D(const Base2D& orig);

    virtual ~Base2D();
    bool Init(int resx,int resy);
    void setImage(std::string path);
    void useShader(int type);

    uint getColorShader();

    virtual void Render();
    virtual void OnClick();

protected:

    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;
    //-----------------
    // Shaders
    //-----------------
    Shader * shader;
    // ints for shader returns

    int _TextureShader;  // the linked shaders
    int _ColorShader;
    int _CurrentShader;

    unsigned int _Texture;

    std::string _ImagePath;

    GLint _Uniform_mv_projectloc;
    GLint _Uniform_colorloc;
    glm::mat4 _Projection;

};

#endif // BASE2D_H
