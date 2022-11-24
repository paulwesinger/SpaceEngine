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
    Base2D(int resx, int resy, Shader * sh);
 //   Base2D(int resx, int resy,std::string path);
    Base2D(int resx, int resy, std::string path, Shader * sh);
    Base2D(const Base2D& orig);

    virtual ~Base2D();
    bool Init(int resx,int resy);
    void setImage(std::string path);
    void useShader(int type);
    void setShaderPtr(Shader * pt);
    Shader * getShaderPtr();

/*
    void setGlyphShader(GLuint sh, bool current = false);
    void setTextureShader (GLuint sh,bool current = false);
    void setColorShader(GLuint sh, bool current = false);

    GLuint getGlyphShader();
    GLuint getColorShader();
    GLuint getTextureShader();
*/
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

    GLuint _TextureShader;  // the linked shaders
    GLuint _ColorShader;
    GLuint _CurrentShader;
    GLuint _GlyphShader;


    unsigned int _Texture;

    std::string _ImagePath;

    GLint _Uniform_mv_projectloc;
    GLint _Uniform_colorloc;
    glm::mat4 _Projection;

};

#endif // BASE2D_H
