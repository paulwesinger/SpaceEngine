#ifndef SHADER_H
#define SHADER_H

#include  <GL/glew.h>
#include <string>
#include <stdio.h>
#include "../fileutils/fileutil.h"

class Shader
{

public:
    Shader();

    // Standard shaders for rendering
    void CreateStandardShaders();
    void CreatStandardShaderFromFile(std::string path);


    GLuint getGlyphShader();
    GLuint getTexture2DShader();
    GLuint getColor2DShader();

    GLuint getTexture3DShader();
    GLuint getColor3DShader();
    GLuint getLightShader();
    GLuint getLightColorShader();


    int compileShader(const char* source, GLint type);
    int compileVertexShader(const char* source); // Vertex und Fragment Shader von Datei
    int compileFragmentShader(const char* source);
    int CreateProgram(int &vs,int &fs); //in vertexshader fragmentshader ret Programmindex
    // Vertex und Fragment Shader von Datei
    int compileVertexShaderFromFile(std::string path,fileUtil * reader);
    int compileFragmentShaderFromFile(std::string path,fileUtil * reader);
    void CreateCustomShader(GLuint &progID );  // Muss VOR AttachCustomShader aufgerufen werden!!
    void AttachCustomShader( GLuint &prog, int &shader);  //Shader dazuhängen
    void CreateCustomProgram(GLuint &prog); // Die ID des Shaders retour
    void deleteShader(int &shader);

    ~Shader();
protected:
    // Shaders for text and 2D
    GLuint _GlyphShader2D,_TextureShader2D,_ColorShader2D;

    //Shaders for 3D
    GLuint _TextureShader3D,_ColorShader3D,_LightShader3D, _LightShaderColor3D;

private:

    bool CreateShaderProgram(GLuint & prg,const GLchar * vertexsource, const GLchar * fragmentsource);
    bool CreateStandardGlyphShader();
    bool CreateStandard2DColorShader();
    bool CreateStandard2DTextureShader();

    bool CreateStandard3DTextureShader();
    bool CreateStandard3DColorShader();
    bool CreateStandard3DLightShader();
    bool CreateStandard3DLightColorShader();

    bool _FAILED_GlyphShader;
    bool _FAILED_2DTextureShader;
    bool _FAILED_2DColorShader;

    bool _FAILED_3DTextureShader;
    bool _FAILED_3DColorShader;
    bool _FAILED_3DLightShader;
    bool _FAILED_3DLightColorShader;

};

#endif // SHADER_H
