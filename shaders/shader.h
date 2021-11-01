#ifndef SHADER_H
#define SHADER_H


#include <string>
#include <stdio.h>
#include  <GL/glew.h>
#include "../fileutils/fileutil.h"


class Shader
{

public:
    Shader();

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

};

#endif // SHADER_H
