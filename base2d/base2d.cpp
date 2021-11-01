#include "base2d.h"


/*
 * File:   Base2D.cpp
 * Author: paul
 *
 * Created on 13. Dezember 2018, 22:13
 */
#include "base2d.h"
#include "../imageloader/loadimage.h"
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../logs/logs.h"
#include "../utils/utils.h"



const int RECT_WIDTH = 200;
const int RECT_HEIGHT = 50;


static const GLchar * vs2D_src = {
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

static const GLchar * fs2D_src = {
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
    "   if(texel.a == 0.0)                                          \n"
    "       discard;                                                \n"
    "   fragcolor =   col2D * texel ;                               \n"
    "}                                                                "
};

static const GLchar * fs2D_ColorSrc = {
    "#version 440 core                                              \n"

    "out vec4 fragcolor;                                            \n"
    "uniform vec4 col2D;                                            \n"

    "void main()                                                    \n"
    "{                                                              \n"
    "   fragcolor =   col2D;                                        \n"
    "}                                                                "
};



static const GLushort vertex_indices[] =
{
    0, 1, 2, 3,4, 5
};

    static const GLfloat vertex_positions[] =
    {
    //  Position             Texture
        0.08f,  -0.5f,      0.0f,1.0f,  //0.0f,
        0.08f,  0.1f,       0.0f,0.0f,  //1.0f,
        0.58f, 0.1f,        0.0f,0.0f,  //1.0f,

        0.58f, -0.5f,       1.0f, 1.0f, //0.0f,
        0.8f, 0.1f,         1.0f, 0.0f, //1.0f,
        0.95f, -0.5f,       1.0f, 1.0f //0.0f,
    };

Base2D::Base2D(int resx, int resy) {
    setImage("");

    _Size.w = RECT_WIDTH;
    _Size.h = RECT_HEIGHT;

    Init(resx, resy);
}

Base2D::Base2D(int resx, int resy, std::string path){
    setImage(path);

    _Size.w = RECT_WIDTH;
    _Size.h = RECT_HEIGHT;

    Init(resx,resy);
}

Base2D::Base2D(const Base2D& orig) {
}

Base2D::~Base2D() {
    if ( shader )
        delete shader;
}

void Base2D::useShader(int type) {
    if ( type == (TEXTURE_SHADER &&  _ImagePath == "") ) {
        _CurrentShader = _ColorShader;
        return;
    }

    switch( type) {
        case TEXTURE_SHADER: _CurrentShader = _TextureShader; break;
        case COLOR_SHADER: _CurrentShader = _ColorShader;  break;
    default:
        _CurrentShader = _TextureShader;
    }
}

void Base2D::setColor(glm::vec4 col) {
    _Color = col;
}
void Base2D::setDisablecolor(glm::vec4 disCol) {
    _DisableColor = disCol;
}

void Base2D::disable(){
    _Enable = false;
}
void Base2D::enable(){
    _Enable = true;
}

bool Base2D::IsEnabled(){
    return _Enable;
}

glm::vec4 Base2D::color() { return  _Color; }


void Base2D::setWidth(int w) {
    _Size.w = w;
}

int Base2D::Width(){
    return _Size.w;
}

int Base2D::Height() {
    return _Size.h;
}
void Base2D::setHeight(int h) {
    _Size.h = h;
}

void Base2D::setSize(int w, int h) {
    _Size.w = w;
    _Size.h = h;
}

void Base2D::setPos(int x, int y) {
    _Pos.x = x;
    _Pos.y = y;
}

bool Base2D::intersect(int x, int y) {
    return  ( ((x > _Pos.x) && (x < _Pos.x + _Size.w) ) &&
              ((y > _Pos.y) && (y < _Pos.y + _Size.h)) ) ? true : false;
}

bool Base2D::Init(int resx, int resy) {

    // ---------------------------
    // Color Init
    //----------------------------
    _Color          = glm::vec4(1.0, 1.0, 1.0, 1.0);
    _DisableColor   = glm::vec4(0.5, 0.5, 0.5, 0.5);
    _Enable = true;

    projection =  glm::ortho(0.0f,static_cast<float>(_ResX), static_cast<float>(_ResY), 0.0f,  -1.0f, 1.0f);

    // ---------------------------
    // Texture Shader init :
    // ---------------------------
    _ResX = resx;
    _ResY = resy;
    shader = new Shader();
    if (shader ) {
        vs = shader -> compileVertexShader(vs2D_src);
        fs = shader -> compileFragmentShader(fs2D_src);
        _TextureShader = shader -> CreateProgram(vs,fs);

        if ( _TextureShader == 0 )
            logwarn("Fehler in den Shadern !!!","Base2D" );
        else
            loginfo( "Shader erstellt ID = " + IntToString(_TextureShader),"Base2D::Init");
    }
    else
        logwarn("Konnte shader nicht erzeurgen","Base2D");

    // -------------------------------
    // Color Shader init
    //--------------------------------

    if (shader) {
        // vs existiert schon;
        fs = shader->compileFragmentShader(fs2D_ColorSrc);
        _ColorShader = shader->CreateProgram(vs,fs);
        if (_ColorShader == 0 )
            logwarn("Fehler beim erstellen des ColorShader !","Base2D::Init");
        else
            loginfo("Erstelle Colorshader ................. done","Base2D::Init");
    }
    else
        logwarn("Klasse Shader konnte nicht initialisiert werden ","Base2D::Init");


    if ( _ImagePath != "") {

        SDL_Surface * surface = CLoadImage::getSurface( _ImagePath,"Base2D");

        char * data = nullptr;
        if ( surface ) {


            data = static_cast<char*>( surface ->pixels);
            _Size.w  = surface-> w;
            _Size.h = surface-> h;
        }

        if ( data ) {

            glGenerateMipmap(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0);
            glGenTextures(1,&texture);
            glBindTexture(GL_TEXTURE_2D,texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glBindTexture(GL_TEXTURE_2D, 0);

            _CurrentShader = _TextureShader;
        }
    }
    else {
        _CurrentShader = _ColorShader;
        _Size.w = RECT_WIDTH;
        _Size.h = RECT_HEIGHT;
    }


    // -----------------------------------------------
    // VertexArraobject und VertexBufferObject
    // -----------------------------------------------
    glGenVertexArrays(1,&_VAO);
    glBindVertexArray(_VAO);
    glGenBuffers(1,&_VBO);
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);

    glBufferData(GL_ARRAY_BUFFER,
 //                 sizeof(vertex_positions),
 //                 vertex_positions,
                 sizeof(GLfloat) * 6 * 4,
                 nullptr,
                 GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 4 * sizeof(GLfloat),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 4 * sizeof(GLfloat),(void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // --------------   Index
    glGenBuffers(1,&_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  sizeof (vertex_indices),
                  vertex_indices,
                  GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    return true;
 }

void Base2D::setImage(std::string path) {
    _ImagePath = path;
}

sPoint Base2D::Pos() {
    return _Pos;
}



void Base2D::OnClick(){}   // Im child überschreiben


// ---------------------------------------------------
// Render Function
// param in [x] - X Position in screencoords
// param in [y] - y Position in screnecoords
// ---------------------------------------------------
void Base2D::Render( ) {

    glUseProgram(_CurrentShader);

    glActiveTexture(GL_TEXTURE0);
    projection =  glm::ortho(0.0f,static_cast<float>(_ResX),static_cast<float>(_ResY), 0.0f,  -1.0f, 1.0f);
    //  projection =  glm::ortho(static_cast<float>(_ResX),0.0f, static_cast<float>(_ResY), 0.0f, -1.0f, 1.0f);

    mv_projectloc = glGetUniformLocation(_CurrentShader,"projection");

    uniform_colorloc   = glGetUniformLocation(_CurrentShader,"col2D");

    glUniform4f(uniform_colorloc, _Color.r, _Color.g, _Color.b, _Color.a);


    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat w = _Size.w;
    GLfloat h = _Size.h;

    GLfloat px = static_cast<GLfloat>(_Pos.x);
    GLfloat py = static_cast<GLfloat>(_Pos.y);


    GLfloat vertices[6][4] = {
            { px,     py  + h,        0.0, 1.0},//0.0 },
            { px,     py,             0.0, 0.0},//1.0 },
            { px + w, py,             1.0, 0.0},//1.0 },

            { px, py + h,             0.0, 1.0},//0.0 }, // w muss weg für 6  uv = 0,0 !!
            { px + w, py,             1.0, 0.0},//1.0 },
            { px + w, py + h,         1.0, 1.0} //0.0 }
    };

    glm::mat4 Model(1.0f);
    glm::mat4 mvp = projection * Model ;
    glUniformMatrix4fv(mv_projectloc, 1, GL_FALSE, glm::value_ptr(mvp)); //projection));


    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    // Texture
    glBindTexture(GL_TEXTURE_2D,texture);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);


    // Aufräumen
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);

}

static inline mat4 ortho(float left, float right, float bottom, float top, float n, float f)
{
    return mat4( vec4(2.0f / (right - left), 0.0f, 0.0f, 0.0f),
                 vec4(0.0f, 2.0f / (top - bottom), 0.0f, 0.0f),
                 vec4(0.0f, 0.0f, 2.0f / (n - f), 0.0f),
                 vec4((left + right) / (left - right), (bottom + top) / (bottom - top), (n + f) / (f - n), 1.0f) );
}
