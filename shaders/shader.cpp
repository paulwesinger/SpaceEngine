#include "shader.h"

#include "shader.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "../logs/logs.h"

Shader::Shader()
{
    //Komment

}
Shader::~Shader()
{}
int Shader::compileVertexShader(const char* source)
{
    int ret = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(ret,1,&source,NULL);
    glCompileShader(ret);
    int ok;
    char log[512];
    glGetShaderiv(ret,GL_COMPILE_STATUS,&ok);
    if (  ! ok )
    {
        glGetShaderInfoLog(ret,512,NULL,log);
        logwarn("Warning: compile failed !" ,"Shader::compileVertexShader" );
        std::cout << "Fehler :" << log << std::endl;

    }
    else
        loginfo("VertexShader: compiled ","Shader::compileVertexShader");

    return ret;

}
int Shader::compileFragmentShader(const char * source)
{
    int ret = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource(ret,1,&source,NULL);
    glCompileShader(ret);
    int ok;
    char log[512];
    glGetShaderiv(ret,GL_COMPILE_STATUS,&ok);
    if ( ! ok)
    {
        glGetShaderInfoLog(ret,512,NULL,log);

        logwarn("Warning: compile failed" ,"Shader::compileFragment Shader");
        std::cout << "Fehler :" << log << std::endl;

    }
    else
        loginfo("Fragment Shader: compiled","Shader::compileFragmentShader");
     return ret;
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
