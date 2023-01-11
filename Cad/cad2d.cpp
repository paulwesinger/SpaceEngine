#include "cad2d.h"

#include "../logs/logs.h"
#include "../utils/utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../defaults.h"




BaseCad2D::BaseCad2D() {}

BaseCad2D::BaseCad2D(int resx, int resy, glm::mat4 perspektive,glm::mat4 ortho){

    matPerspective = perspektive;
    matOrtho = ortho;
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
        std::string vertex_source = PATH::ROOT + "ShaderSources/cad2Dshader.vex";
        std::string frag_source = PATH::ROOT + "ShaderSources/cad2Dshader.frg";

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

        _CurrentShader = _ColorShader;
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
                 sizeof(GLfloat) * MAX_POINTS * 3 ,
                 nullptr,
                 GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);


    // --------------   Index
    return true;
}



void BaseCad2D::useShader(GLuint s) {
    _CurrentShader = s;
}

void BaseCad2D::Render(){

    glUseProgram(_CurrentShader);

    GLfloat x = static_cast<GLfloat>(_P0.x);
    GLfloat y = static_cast<GLfloat>(_P0.y);
    GLfloat x1 = static_cast<GLfloat>(_P1.x);
    GLfloat y1 = static_cast<GLfloat>(_P1.y);

    GLfloat vertices[4][3] = {
        {x, y, 0.0},
        {x1, y1, 0.0},
        {200, 100, 0.0},
        {200, 900, 0.0}
       };

    projection =  glm::ortho(0.0f,static_cast<float>(_ResX),static_cast<float>(_ResY), 0.0f,  -1.0f, 1.0f);


    GLint color_loc = glGetUniformLocation(_ColorShader,"col2D");
    mv_projectloc = glGetUniformLocation(_CurrentShader,"projection");

    glm::mat4 Model(1.0f);
//    glm::mat4 mvp = projection * cam->GetView() *  Model ;
    //glm::mat4 mvp =  matOrtho * cam ->GetView() *  Model;
    glm::mat4 mvp =  projection * Model;

    glUniformMatrix4fv(mv_projectloc, 1, GL_FALSE, glm::value_ptr(mvp)); //projection));
    glUniform4f(color_loc,_Color.r,_Color.g,_Color.b,_Color.a);

    GLint oldMode;
    glGetIntegerv(GL_POLYGON_MODE,&oldMode);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);
    glBufferSubData(GL_ARRAY_BUFFER,0,_Points.size() * sizeof(Point),&_Points[0]);

    glLineWidth(5.0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawArrays( GL_LINES, 0, _Points.size());


    glLineWidth(1.0);

/*
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawArrays( GL_LINES, 0,4);

*/
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

void BaseCad2D::addPoint(Point p) {
    _Points.push_back(p);
}

void BaseCad2D::addPoint(int x, int y) {
    _Points.push_back(Point(x,y));

}

glm::vec2 BaseCad2D::Pos0(){
    return _P0;
}

glm::vec2 BaseCad2D::Pos1(){
    return _P1;
}

bool BaseCad2D::intersectP0(sPoint p0, sPoint mouse){
    if (intersect(mouse.x,mouse.y)) {
        //
    }
}
bool BaseCad2D::intersectP1(sPoint p1, sPoint mouse){

    // !!!!!!!!!!!
    return false;
}
void BaseCad2D::OnClick() {}

void BaseCad2D::setDisablecolor(glm::vec4 disCol){}
void BaseCad2D::setColor(glm::vec4 col){
    _Color = col;
}
void BaseCad2D::disable(){}
void BaseCad2D::enable(){}

bool BaseCad2D::IsEnabled(){}

