#include "shader.h"

#include "shader.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "../logs/logs.h"



static const char vertexshadersource[]=
        "#version 440 core 					\n"
        "out vec4 vs_color;					\n"
        "layout (location = 0) in vec4 offsett;			\n"
        "layout (location = 1) in vec4 color;	                \n"
        "void main(void)					\n"
            "{							\n"
        "	const vec4 vertices[] = vec4[](vec4(0.25,-0.25,0.5,1.0),\n"
        "			  	vec4(-0.25,-0.25,0.5,1.0),\n"
        "			  	vec4(0.25,0.25,0.5,1.0));\n"
        "						           \n"
        "	const vec4 colors[] = vec4[](vec4(1.0f,0.0f,0.0f,1.0f),\n"
        "        		      vec4(0.0f,1.0f,0.0f,1.0f),\n"
        "			      vec4(0.0f,0.0f,1.0f,1.0f));\n"
        "							   "
        "	gl_Position = vertices[gl_VertexID]+offsett;	\n"
        "      // oder :  vs_color = colors[gl_VertexID];       \n"
        "       vs_color = color;  		  		\n"
                "							\n"
        "}							\n";
static const char* fragmentshadersource=
        "#version 440 core  					\n"
                "							\n"
        "in vec4 vs_color;					\n"
        "out vec4 fragcolor;					\n"
        "void main(void)					\n"
        "{							\n"
            "	fragcolor = vs_color;				\n"
        "}";


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
        //fprintf(stdout,"Fehlermeldung:",log );
        std::cout << "Fehler :" << log <<  ok << std::endl;
                logwarn("Warning " + (std::string)log,"Shader::VertexShader" );
    }
    else
        fprintf(stdout,"Vertex Shader compile erfolgreich\n");

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
        //fprintf(stdout,"Fehlermeldung:",log );
        std::cout << "Fehler :" << log << std::endl;
                logwarn("Warning :" + (std::string) log,"Shader::Fragment Shader");
    }
    else
        fprintf(stdout,"Fragment Shader compile erfolgreich\n");
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
          logwarn("Shader Source nicht gefunden","Shader::compileVertexShaderFromFile");
          logwarn("Fehler: " + shadertext + "Path : " + path," Shader:: readFromFile");

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
          loginfo("VertexShader erfolgreich compiliert !","Shader::compileVertexShaderFromFile");
          return ret;
      }
      else {
        glGetShaderInfoLog(ret,512,NULL,log);
    //fprintf(stdout,"Fehlermeldung:",log );
    std::cout << "Fehler :" << log << std::endl;
        logwarn("Warning :" + (std::string) log,"Shader::compileVertexShaderFromCource");
        return -1;
      }
}

int Shader::compileFragmentShaderFromFile(std::string path, fileUtil* reader) {
      std::string shadertext;
      if ( ! reader->readShaderSource(shadertext,path)  ) {
          logwarn("Shader Source nicht gefunden","Shader::compileFragmentShaderFromFile");
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
          loginfo("FragmentShader erfolgreich compiliert !","Shader::compileFragmentShaderFromFile");
          return ret;
      }
      else {
        glGetShaderInfoLog(ret,512,NULL,log);
    //fprintf(stdout,"Fehlermeldung:",log );
    std::cout << "Fehler :" << log << std::endl;
        logwarn("Warning :" + (std::string) log,"Shader::compileFragmentShaderFromCource");
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
