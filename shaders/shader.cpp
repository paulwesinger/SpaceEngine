#include "shader.h"

#include "shader.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "../logs/logs.h"
#include "../error/error.h"

//----------------------------
// Shader für Text Rendering
// ---------------------------
static const GLchar * Standard2D_VertexSrc = {
    "#version 440 core                                              \n"
    "layout (location = 0) in vec2 vertex;                          \n"
    "layout (location = 1) in vec2 tex;                             \n"

    "uniform mat4 projection;                                       \n"
    "out VS_OUT {                                                   \n"
    "   vec2 uv;                                                    \n"
    "} vs_out;                                                      \n"

    "void main()                                                    \n"
    "{                                                              \n"
    "   gl_Position = projection * vec4(vertex,0.0,1.0);            \n"
    "   vs_out.uv =  tex;                                           \n"
   "}                                                               \n"
};

static const GLchar * Standard2DTexture_FragmentSrc = {
    "#version 440 core                                              \n"

    "in VS_OUT {                                                    \n"
    "   vec2 uv;                                                    \n"
    "} fs_in;                                                       \n"

    "out vec4 fragcolor;                                            \n"
    "uniform sampler2D text;                                        \n"
    "uniform vec4 col2D;                                            \n"

    "void main()                                                    \n"
    "{                                                              \n"
    "   vec4 texel = texture(text,fs_in.uv);                        \n"
    "   if(texel.r == 0.0 && texel.g == 0.0 && texel.b == 0)        \n"
    "       discard;                                                \n"
    "   else {                                                      \n"
    "       vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, fs_in.uv).r); \n"
    "       fragcolor =    sampled * col2D;                         \n"
    "   }                                                           \n"
    "}                                                                "
};

static const GLchar * Standard2DColor_FragmentSrc = {
    "#version 440 core                                              \n"

    "out vec4 fragcolor;                                            \n"
    "uniform vec4 col2D;                                            \n"

    "void main()                                                    \n"
    "{                                                              \n"
    "   fragcolor =   col2D;                                        \n"
    "}                                                                "
};



//-----------------------------
// Shader für Texture Rendering
// ----------------------------
const GLchar * Standard3D_VertexSrc = {
    "#version 450 core                                          \n"

    "layout (location = 0) in vec3 position;                    \n"
    "layout (location = 1) in vec3 veccolor;                    \n"
    "layout (location = 2) in vec2 tex;                         \n"

    "out VS_OUT{                                                \n"
    "   vec4 color;                                             \n"
    "   vec2 TexCoord;                                          \n"
    "}  vs_out;                                                 \n"

    "uniform mat4 mv_matrix;                                    \n"

    "uniform mat4 model;                                        \n"
    "uniform mat4 projection;                                   \n"
    "uniform mat4 view;                                         \n"

    "void main(void)                                            \n"
    "{                                                          \n"
    "   vec3 fragpos = vec3(model * vec4(position,1.0));        \n"
    "   gl_Position = projection * view * vec4(fragpos,1.0);    \n"

    "   vs_out.color = vec4(veccolor,1.0);                      \n"
    "   vs_out.TexCoord = tex;                                  \n"
    "}                                                          \n"
};

const GLchar * Standard3DTextured_FragmentSrc = {

    "#version 450 core                                          \n"

    "layout(binding=0) uniform sampler2D texture1;              \n"
    "layout(binding=1) uniform sampler2D texture2;              \n"

    "in VS_OUT{                                                 \n"
    "   vec4 color;                                             \n"
    "   vec2 TexCoord;                                          \n"
    "} fs_in;                                                   \n"

    "uniform bool useTexture_2;                                 \n"
    "uniform vec4 triangleColor;                                \n"
    "uniform bool hasTexture;                                   \n"

    "out vec4 FragColor;                                        \n"

    "void main(void) {                                          \n"

    "    vec4 outcolor;                                         \n"

    "    if ( hasTexture ) {                                    \n"

    "        if (useTexture_2 )                                 \n"
    "            outcolor = mix(texture(texture1, fs_in.TexCoord), texture(texture2, fs_in.TexCoord), 0.5);\n"
    "        else                                               \n"
    "            outcolor = texture(texture2,fs_in.TexCoord);   \n"
    "    }                                                      \n"
    "    else {                                                 \n"
    "        outcolor =  triangleColor;                         \n"
    "    }                                                      \n"
    "    FragColor =  outcolor;                                 \n"
    "}                                                          \n"

};


const GLchar * Standard3DColored_FragmentSrc = {
    "#version 450 core                                          \n"

    "layout (location = 1) in vec3 veccolor;                    \n"
    "layout (location = 2) in vec2 tex;                          \n"
    "out vec4 color;                                            \n"
    "uniform vec3 triangleColor;                                \n"

    "in VS_OUT                                                  \n"
    "{                                                          \n"
    "vec4 color;                                                \n"
    "vec2 TexCoord;                                             \n"
    "} fs_in;                                                   \n"

    "void main(void)                                            \n"
    "{                                                          \n"
    "    color = fs_in.color;                                   \n"
    "}                                                          \n"
};




//----------------------------
// Shader für Color Rendering
// ---------------------------



Shader::Shader()
{
    _FAILED_GlyphShader         = false;
    _FAILED_3DTextureShader     = false;
    _FAILED_3DColorShader       = false;
    _FAILED_2DColorShader       = false;
    _FAILED_2DTextureShader     = false;

    CreateStandardShaders();
}


void Shader::CreatStandardShaderFromFile(std::string path) {


}

void Shader::CreateStandardShaders() {

    //------------------------------------------------------
    //Create Shader for Text printing and 2D
    //------------------------------------------------------
    Error::Failed(CreateStandardGlyphShader(),"Creating GlyphShader failed",_FAILED_GlyphShader);
    Error::Failed(CreateStandard2DTextureShader(),"Creating 2D TextureShader failed !", _FAILED_2DTextureShader);
    Error::Failed(CreateStandard2DColorShader(),"Creating 2D ColorShader failed !", _FAILED_2DColorShader);


    //------------------------------------------------------
    //Create Shader for 3D rendering with texture, no lights
    //------------------------------------------------------
    Error::Failed(CreateStandard3DTextureShader(),"Creating Standard3DTextureShader failed !", _FAILED_3DTextureShader);

    //------------------------------------------------------
    //Create Shader for 3D rendering with color, no lights
    //------------------------------------------------------
    Error::Failed(CreateStandard3DColorShader(),"Creating Standard3DColorShader failed !", _FAILED_3DColorShader);
}



bool Shader::CreateStandardGlyphShader() {

    //------------------------------------------------------
    //Shader for text printing
    //------------------------------------------------------
    int vs = compileShader(Standard2D_VertexSrc,GL_VERTEX_SHADER);
    int fs = compileShader(Standard2DTexture_FragmentSrc,GL_FRAGMENT_SHADER);
    _GlyphShader2D = CreateProgram(vs,fs);

    if (  vs == 0 ||  fs == 0  || _GlyphShader2D == 0 )
        return false;

     return true;
}

bool Shader::CreateStandard2DTextureShader() {

    //------------------------------------------------------
    //Shader for text printiing and background with alpha
    //------------------------------------------------------
    int vs = compileShader(Standard2D_VertexSrc,GL_VERTEX_SHADER);
    int fs = compileShader(Standard2DTexture_FragmentSrc,GL_FRAGMENT_SHADER);
    _TextureShader2D = CreateProgram(vs,fs);

    if (  vs == 0 ||  fs == 0  || _TextureShader2D == 0 )
        return false;

     return true;
}

bool Shader::CreateStandard2DColorShader() {

    //------------------------------------------------------
    //Shader for text printing
    //------------------------------------------------------
    int vs = compileShader(Standard2D_VertexSrc,GL_VERTEX_SHADER);
    int fs = compileShader(Standard2DColor_FragmentSrc,GL_FRAGMENT_SHADER);
    _ColorShader2D = CreateProgram(vs,fs);

    if (  vs == 0 ||  fs == 0  || _ColorShader2D == 0 )
        return false;

     return true;
}

bool Shader::CreateStandard3DTextureShader() {
    //------------------------------------------------------
    //Shader for text printing
    //------------------------------------------------------
    int vs = compileShader(Standard3D_VertexSrc,GL_VERTEX_SHADER);
    int fs = compileShader(Standard3DTextured_FragmentSrc,GL_FRAGMENT_SHADER);
    _TextureShader = CreateProgram(vs,fs);

    if (  vs == 0 ||  fs == 0  || _TextureShader == 0 )
        return false;

    return true;
}

bool Shader::CreateStandard3DColorShader() {
    //------------------------------------------------------
    //Shader for text printing
    //------------------------------------------------------
    int vs = compileShader(Standard3D_VertexSrc,GL_VERTEX_SHADER);
    int fs = compileShader(Standard3DColored_FragmentSrc,GL_FRAGMENT_SHADER);
    _ColorShader = CreateProgram(vs,fs);

    if (  vs == 0 ||  fs == 0  || _ColorShader == 0 )
        return false;

    return true;
}

GLuint Shader::getTexture3DShader() {
   return ( _FAILED_3DTextureShader) ?  0 : _TextureShader;
}

GLuint Shader::getColor3DShader() {
   return ( _FAILED_3DColorShader) ?  0 : _ColorShader;
}

GLuint Shader::getGlyphShader() {
   return ( _FAILED_GlyphShader) ?  0 : _GlyphShader2D;
}

GLuint Shader::getColor2DShader() {
    return _ColorShader2D;
}

GLuint Shader::getTexture2DShader() {
    return _TextureShader2D;
}



Shader::~Shader(){

}

int Shader::compileShader(const char* source, GLint type){

    int ret = glCreateShader(type); // VERTEX,FRAGMENT or GEOMETRY

    glShaderSource(ret,1,&source,NULL);
    glCompileShader(ret);
    int ok;
    char log[512];

    glGetShaderiv(ret,GL_COMPILE_STATUS,&ok);
    if (  ! ok )
    {
        glGetShaderInfoLog(ret,512,NULL,log);
        logwarn( "FAILED : " +(std::string)log);
        return 0;
    }

    loginfo("VertexShader: compiled ","Shader::compileVertexShader");
    return ret;
}


int Shader::compileVertexShader(const char* source)
{
    return compileShader(source,GL_VERTEX_SHADER);
}
int Shader::compileFragmentShader(const char * source)
{
    return compileShader(source,GL_FRAGMENT_SHADER);
}



int Shader::CreateProgram(int &vs,int &fs)
{
    GLuint prog = glCreateProgram();
    glAttachShader(prog,vs);
    glAttachShader(prog,fs);
    glLinkProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

// NEue Funktionen für CustomShader from File
int Shader::compileVertexShaderFromFile(std::string path, fileUtil* reader) {
      std::string shadertext;
      if ( ! reader->readShaderSource(shadertext,path)  ) {
          logwarn("Shader Source nicht gefunden: " + path,"Shader::compileVertexShaderFromFile");
          return -1;
      }
      loginfo("Source " + path + " geladen !","Shader::compileVertexShaderFromFile");

      int ret = glCreateShader(GL_VERTEX_SHADER);
      const GLchar* ch = (const GLchar* )shadertext.c_str();

      glShaderSource(ret,1,&ch ,NULL );
      glCompileShader(ret);

      int ok;
      char log[512];
      glGetShaderiv(ret,GL_COMPILE_STATUS,&ok);
      if ( ok ) {
          loginfo("VertexShader " + path + " erfolgreich compiliert !","Shader::compileVertexShaderFromFile");
          return ret;
      }
      else {
        glGetShaderInfoLog(ret,512,NULL,log);
        logwarn("Warning : "+ path + "failed:" + (std::string) log,"Shader::compileVertexShaderFromCource");
        return -1;
      }
}

int Shader::compileFragmentShaderFromFile(std::string path, fileUtil* reader) {
      std::string shadertext;
      if ( ! reader->readShaderSource(shadertext,path)  ) {
          logwarn("Shader Source nicht gefunden: " + path,"Shader::compileFragmentShaderFromFile");
          return -1;
      }
      loginfo("Source " + path + "  geladen !","Shader::compileFragmentShaderFromFile");
      int ret = glCreateShader(GL_FRAGMENT_SHADER);
      const GLchar* ch = (const GLchar* )shadertext.c_str();

      glShaderSource(ret,1, &ch, NULL );
      glCompileShader(ret);

      int ok;
      char log[512];
      glGetShaderiv(ret,GL_COMPILE_STATUS,&ok);
      if ( ok ) {
          loginfo("FragmentShader: " + path + " erfolgreich compiliert !","Shader::compileFragmentShaderFromFile");
          return ret;
      }
      else {
        glGetShaderInfoLog(ret,512,NULL,log);
        logwarn("Warning :" + path + " Log: " +(std::string) log,"Shader::compileFragmentShaderFromCource");
        return -1;
      }
}

void Shader::CreateCustomShader(GLuint &progID ){
    progID = glCreateProgram();
    loginfo("Erstelle ShaderID ........ done","Shader::CreateCustomShader");
}

void Shader::AttachCustomShader( GLuint &prog, int &shader) {
    glAttachShader(prog,shader);
}

void Shader::CreateCustomProgram(GLuint &prog) {
    glLinkProgram(prog);
}

void Shader::deleteShader(int& shader) {
    glDeleteShader(shader);
}
