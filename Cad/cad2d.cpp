#include "cad2d.h"

#include "../logs/logs.h"
#include "../utils/utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const GLfloat vertex_positions[] =
{
//  Position
    0.08f,  -0.5f,
    0.08f,  0.1f,
    0.58f, 0.1f,

    0.58f, -0.5f,
    0.8f, 0.1f,
    0.95f, -0.5f,
};

BaseCad2D::BaseCad2D() {}

BaseCad2D::BaseCad2D(int resx, int resy){
    Init(resx,resy);
}

BaseCad2D::~BaseCad2D() {
    if (filestream)
        delete filestream;
}

bool BaseCad2D::Init(int resx,int resy) {
    // ---------------------------
    // Color Init
    //----------------------------
    _Color          = glm::vec4(1.0, 1.0, 1.0, 1.0);
    _DisableColor   = glm::vec4(0.5, 0.5, 0.5, 0.5);
    _Enabled = true;

    // ---------------------------
    // Texture Shader init :
    // ---------------------------
    _ResX = resx;
    _ResY = resy;
    shader = new Shader();

    // -------------------------------
    // filestream init
    //--------------------------------
    filestream = new fileUtil();

    // -------------------------------
    // Color Shader init
    //--------------------------------
    if (shader) {

        int vs;
        int fs;
        std::string vertex_source = "../SpaceEngine/ShaderSources/cad2Dshader.vex";
        std::string frag_source = "../SpaceEngine/ShaderSources/cad2Dshader.frg";

        vs = shader -> compileVertexShaderFromFile(vertex_source,filestream);
        fs = shader -> compileFragmentShaderFromFile(frag_source,filestream);

         // ColorCubeShader
        loginfo("Erstelle Cube Color Shader.................done");
        shader->CreateCustomShader(_ColorShader);
        shader->AttachCustomShader(_ColorShader,vs);
        shader->AttachCustomShader(_ColorShader,fs);
        shader->CreateCustomProgram(_ColorShader);
        glDetachShader(_ColorShader,vs);
        glDetachShader(_ColorShader,fs);
        logEmptyLine();
    }
    else
        logwarn("Warning: Failed create shader","cad2D::Init");

    // -----------------------------------------------
    // VertexArraobject und VertexBufferObject
    // -----------------------------------------------
    glGenVertexArrays(1,&_VAO);
    glBindVertexArray(_VAO);
    glGenBuffers(1,&_VBO);
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);

    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 4,
                 nullptr,
                 GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0,1,GL_FLOAT,GL_FALSE,0,(void*)0);
    glEnableVertexAttribArray(0);

    // --------------   Index
    return true;
}

void BaseCad2D::useShader(int type) {

    //--------------------------------------------
    // type sollte hier dash, dotted usw sein.....
    //--------------------------------------------
    _CurrentShader = _ColorShader;
}

void BaseCad2D::Render(){

    GLfloat vertices[4] = {
         (_P0.x, _P0.y, _P1.x, _P1.y)
       };

    projection =  glm::ortho(0.0f,static_cast<float>(_ResX),static_cast<float>(_ResY),
                             0.0f,  -1.0f, 1.0f);
    GLint color_loc = glGetUniformLocation(_ColorShader,"col2D");
    mv_projectloc = glGetUniformLocation(_CurrentShader,"projection");

    glm::mat4 Model(1.0f);
    glm::mat4 mvp = projection * Model ;

    glUniformMatrix4fv(mv_projectloc, 1, GL_FALSE, glm::value_ptr(mvp)); //projection));
    glUniform4f(color_loc,_Color.r,_Color.g,_Color.b,_Color.a);

    GLint oldMode;
    glGetIntegerv(GL_POLYGON_MODE,&oldMode);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);


    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawArrays( GL_LINE_STRIP	, 0, sizeof(vertices));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK,oldMode);
}

void BaseCad2D::setPoint0(sPoint p0) {
    _P0.x = p0.x;
    _P0.y = p0.y;
}

void BaseCad2D::setPoint1(sPoint p1) {
    _P1.x = p1.x;
    _P1.y = p1.y;
}

glm::vec2 BaseCad2D::Pos0(){
    return _P0;
}

glm::vec2 BaseCad2D::Pos1(){
    return _P1;
}

bool BaseCad2D::intersectP0(sPoint p0, sPoint mouse){}
bool BaseCad2D::intersectP1(sPoint p1, sPoint mouse){}
void BaseCad2D::OnClick() {}

void BaseCad2D::setDisablecolor(glm::vec4 disCol){}
void BaseCad2D::setColor(glm::vec4 col){
    _Color = col;
}
void BaseCad2D::disable(){}
void BaseCad2D::enable(){}

bool BaseCad2D::IsEnabled(){}

