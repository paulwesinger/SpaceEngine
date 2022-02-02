#include "textrender.h"
/*
 * File:   TextRender.cpp
 * Author: paul
 *
 * Created on 23. Juni 2019, 11:23
 */
#include "textrender.h"
#include <string>
#include <SDL2/SDL_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../imageloader/loadimage.h"

#define RECT_WIDTH  500
#define RECT_HEIGHT 200

//----------------------------
// Shader für Text Rendering
// ---------------------------
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
    "   if(texel.r == 0.0 && texel.g == 0.0 && texel.b == 0)        \n"
    "       discard;                                                \n"
    "   else {                                                      \n"
    "       vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, fs_in.uv).r); \n"
    "       fragcolor =    sampled * col2D;                         \n"
    "   }                                                           \n"
    "}                                                                "
};
// -------------------------------------------------------
// 3 x VertexShader für linken ,mittleren und rechten Teil
// -------------------------------------------------------
//....
static const GLchar * vertex_textfeld_src = {
    "#version 440 core                                  \n"
    "layout (location = 0) in vec2 vertex;              \n"
    "layout (location = 1) in vec2 tex;                 \n"
    "uniform mat4 projection_textfeld;                  \n"
    "out VS_OUT{                                        \n"
        "vec2 texcoords;                                \n"
    "} vs_out;                                          \n"

    "void main() {                                      \n"
    "   gl_Position = projection_textfeld * vec4(vertex,0.0,1.0); \n"
    "   vs_out.texcoords  =  tex;                       \n"
    "}"
};
// ---------------------------------------------------------
// 3 y Fragmentshader für linkem, mittleren und rechten Teil
// ---------------------------------------------------------
//...
static const GLchar * fragment_textfeld_src = {
    "#version 440 core                              \n"
    "out vec4 fragcolor;                            \n"
    "uniform sampler2D text;                        \n"

    "uniform vec4 color;                            \n"
    "in VS_OUT {                                    \n"
    "   vec2 texcoords;                             \n"
    "} fs_in;                                       \n"
    "void main() {                                  \n"
    "   vec4 texel = texture(text,fs_in.texcoords);       \n"
    "       if ( texel.r == 0.0 && texel.g == 0.0 && texel.b == 0.0 ) {   \n"
    "           discard;                            \n"
    "       }                                       \n"
    "       else {                                  \n"
    "           fragcolor = texel *  color;         \n"

    "       }                                       \n"
    "}                                              "
};

// Fragmentshader COLOR
static const GLchar * fragment_textfeld_Color = {
    "#version 440 core                              \n"

    "out vec4 fragcolor;                            \n"
    "uniform vec4 color;                            \n"

    "void main() {                                  \n"
    "   fragcolor = color; \n"
    "}                                              "
};

// Element Indices
static const GLushort vertex_indices[] =
{
    0, 1, 2, 3, 4, 5
};

TextRender::TextRender(int resx, int resy) {
    Init(resx, resy);
}

TextRender::TextRender(int resx, int resy, sPoint pos) {

    posX = (GLfloat) pos.x;
    posY = (GLfloat) pos.y;
    Init(resx, resy);
}


TextRender::TextRender(const TextRender& orig) {
}

TextRender::~TextRender() {
    if ( shader )
        delete shader;
}

// -----------------------------------------------------------------------
// Look and feel
// -----------------------------------------------------------------------
uint TextRender::getStringCount() { return _StringList.size(); }


void TextRender::setText(uint index, std::string newString) {
    try {
        _StringList.at(index) = newString;
    }
    catch (const std::exception& e) { // reference to the base of a polymorphic object
        loginfo(e.what());
    }
}

void TextRender::setPos(sPoint pos) {
    posX = (GLfloat)pos.x;
    posY = (GLfloat)pos.y; //_ResY - posY;
    //posY = (GLfloat) _ResY - pos.y;
    _Pos = pos;
}

sPoint TextRender::Pos() {
    return _Pos;
}

int TextRender::getTextAreaHeight(){
    return _StringList.size() * _Scale * _Pixelsize + _MarginY * 2;
}

int TextRender::getWidth() {
    return (int)_Textfeld.w;
}

int TextRender::getHeight() {
   return (int)_Textfeld.h;
}



void TextRender::alignToRectSize(int w, int h) {
    int margX = (w - _Textfeld.w) / 2;
    int margY = (h - _Textfeld.h) / 2;

    logwarn("margeX: " + IntToString(margX));
    logwarn("margey: " + IntToString(margY));

    logwarn("w : " + IntToString(w));
    logwarn("w : " + IntToString(h));

    logwarn("TextFeldX: " + IntToString(_Textfeld.w));
    logwarn("TextFeldY: " + IntToString(_Textfeld.h));

    posX += margX;
    posY -= margY;

}


void TextRender::SetHasBottom(bool hasbottom) {_RenderBottom = hasbottom;}
void TextRender::SetHasHeader(bool hasheader) {_RenderHeader = hasheader;}
void TextRender::SetHasBackground(bool hasbg) {_HasBackground = hasbg; }

void TextRender::SetTextColor(glm::vec4 col) { _TextColor = col; }
void TextRender::SetBackgroundColor(glm::vec4 col) { _BackgroundColor = col; }
void TextRender::SetHasTexture(bool hasTex) { _HasTexture = hasTex; }
void TextRender::AddString(std::string s) { _StringList.push_back(s); }
void TextRender::SetAlignRight(bool align) {_AlignRight = align; }
void TextRender::SetScale(GLfloat scale){ _Scale = scale; }




bool TextRender::Init(int resx, int resy) {
    // ---------------------------
    // Shader init :
    // ---------------------------
    _ResX = resx;
    _ResY = resy;
    _RenderBottom = false;
    _RenderHeader = false;
    _HasBackground = false;
    _HasTexture = false;
    _AlignRight = false;
    _BackgroundColor = glm::vec4(0.0f,0.0f,0.8f,0.3f);
    _TextColor = glm::vec4(1.0f,1.0f,1.0f,1.0f);
    _Scale = 1.0f;

    _Pixelsize = 16;
    _MarginLeft = 5.0f;
    _MarginRight= 5.0f;
    _MarginY = 5.0f;

    shader = new Shader();
    if (shader ) {
        vs = shader -> compileVertexShader(vs2D_src);
        fs = shader -> compileFragmentShader(fs2D_src);
        shader2D = shader -> CreateProgram(vs,fs);

        if ( ( vs == 0 ) ||
             ( fs == 0 ) ||
             (shader2D == 0 ) )
            logwarn("Fehler in den Shadern !!!","TextRender; ;Init" );
        else
            logwarn( "Shader erstellt ID = " + IntToString(shader2D),"TextRender::Init");

        // ------------------------------------------------
        // Vertex und Fragment Shader für Textfeld erzeugen
        // ------------------------------------------------
        vs_textfeld = shader -> compileVertexShader(vertex_textfeld_src);
        fs_textfeld = shader -> compileFragmentShader(fragment_textfeld_src);
        shader_textfeld = shader ->CreateProgram(vs_textfeld,fs_textfeld);
        if ( ( vs_textfeld == 0 ) ||
             ( fs_textfeld == 0 ) ||
             (shader_textfeld == 0 ) )
            logwarn("Fehler: Konnte Textfeld - Shader nicht erzeugen !!!","TextRender;;Init" );
        else
            logwarn( "Textfeld Shader erstellt ID = " + IntToString(shader2D),"TextRender::Init");


    }
    else
        logwarn("Konnte shader nicht erzeurgen","TextRender::Init");

    // Color Shader erzeugen
    fs = shader->compileFragmentShader(fragment_textfeld_Color);
    shaderColorTextfeld = shader->CreateProgram(vs_textfeld,fs);
    if ( shaderColorTextfeld == 0)
        logwarn("Konnte TextfeldColorShader nicht erzeugen ","TextRender::compileColorShader");
    else
        loginfo("Texfeld Color Shader erzeugt! ","TextRender::compilecolorshader");



    // ---------------------------------------
    //  Freetype2 init.
    // ---------------------------------------
    if (FT_Init_FreeType(&ft))
        logwarn("Konnte Freetype nicht initialisieren !!","TextRender::Init");
    else
        loginfo("Freetype2 initialisiert ","TextRender::Init");

    if (FT_New_Face(ft, "/usr/share/fonts/adobe-source-code-pro/SourceCodePro-Medium.otf", 0, &face))
    //if (FT_New_Face(ft, "/usr/share/fonts/liberation-mono/LiberationMono-Regular.ttf", 0, &face))
        logwarn("Konnte Freetype2 Face nicht initialisieren","RenderText::Init");
    else
        loginfo("Freetype2 Face initialisiert ... ","TextRender::Init");


    FT_Set_Pixel_Sizes(face, 0, _Pixelsize);

    //if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    //    logwarn("Char X konnte nicht geladen werden !","TextRender::Init");
    //else
    //    loginfo("Char X geladen ","TextRender::Init");

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    // Char 0 .. 127 einlesen
    glActiveTexture(GL_TEXTURE0);
    for (GLubyte c = 0; c < 128; c++)    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            logwarn( "ERROR::FREETYTPE: Failed to load Glyph","TextRender::Init");
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            static_cast<GLsizei>(face->glyph->bitmap.width),
            static_cast<GLsizei>(face->glyph->bitmap.rows),
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x,
            face->glyph->bitmap.rows
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // -------------------------
    // Grafiken für Textfenster
    //--------------------------
    if (GenTextfeldSegment("Headline.png",texHeadline))
        loginfo("Generiere Headline....","TextRender::Init");
    else
        logwarn("Headline.... fehlgeschlagen !!","TextRender::Init");

   // glActiveTexture(GL_TEXTURE0 + 2);
    if (GenTextfeldSegment("Textfeld.png",texPaintarea))
        loginfo("Generiere Textfeld....","TextRender::Init");
    else
        logwarn("Textfeld.... fehlgeschlagen !!","TextRender::Init");

    //glActiveTexture(GL_TEXTURE0 + 4);
    if (GenTextfeldSegment("Bottom.png",texBottom))
        loginfo("Generiere Bottom....","TextRender::Init");
    else
        logwarn("Bottom... fehlgeschlagen !!","TextRender::Init");
    //  -----------------------------------------------
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
    // TextureCoordinates
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 4 * sizeof(GLfloat),(void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Nicht benutzt - säre für Color !
    //glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),(void*)(5* sizeof(float)));
    // glEnableVertexAttribArray(2);
    // --------------   Index
    glGenBuffers(1,&_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  sizeof (vertex_indices),
                  vertex_indices,
                  GL_DYNAMIC_DRAW);
    // ---------------------------------------------------------------
    // Das ganze jetzt für Background
    // Es werden 5 Textuuren benötigt --> Links oben, Rechts oben, Rahmen, Links unten, Rechts unten.
    // An die Textlänge wird nur der Mittelteil angepast.
    // ----------------------------------------------------------------
    // VertexArray für Headline
    glGenVertexArrays(1,&_bgVAO);
    glBindVertexArray(_bgVAO);
    // ****************************************************************
    // ----------------------------------------------------------------
    // Das ganze jetzt noch mal für den Mittelteil und die Eckteile
    // ----------------------------------------------------------------
    // VertexBuffer
    glGenBuffers(1,&_bgVBO);
    glBindBuffer(GL_ARRAY_BUFFER,_bgVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*6*4, NULL, GL_DYNAMIC_DRAW);  // wird in paint angepasst
    // Mittel Teil
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    //TexturCoordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),(void*)(2 * sizeof(float)) );
    glEnableVertexAttribArray(1);
    //-------------------
    //Elementbuffer
    //-------------------
    glGenBuffers(1,&_bgEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bgEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(vertex_indices),
                 vertex_indices,
                 GL_DYNAMIC_DRAW);
    //----------
    // Aufräumen
    //----------
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    return true;

 }

bool TextRender::GenTextfeldSegment(std::string image, unsigned int &tex) {

    std::string imagepath = "images/" + image;
    //glBindTexture(GL_TEXTURE_2D,tex);
    SDL_Surface * surface;
    char * data;
    surface = CLoadImage::getSurface(imagepath,"TextRender::GenTextFeldSegment");

    if (surface) {
        data = static_cast<char*>( surface ->pixels);
        _Textfeld.w = surface -> w;
        _Textfeld.h = surface -> h;
    }
    else
        return false;

    if (data) {
        glGenTextures(1,&tex);
        glBindTexture(GL_TEXTURE_2D,tex);
        //Flags
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    }
    return false;
}

void TextRender::RenderPaintarea(GLfloat x, GLfloat y, GLfloat height) {

    // Standard Masse der images !!
    GLfloat w = _Textfeld.w;
    //GLfloat h = 16.0f;

    GLfloat vertices[6][4] = {

         { x,     y  + height,          0.0, 0.0 },
         { x,     y,                    0.0, 1.0 },
         { x + w, y,                    1.0, 1.0 },

         { x, y  +  height,             0.0, 0.0 }, // w muss weg für 6  uv = 0,0 !!
         { x + w, y,                    1.0, 1.0 },
         { x + w, y + height,           1.0, 0.0 }
    };

    if (_HasTexture) {
        glUniform4f(framecolor_loc,1.0,1.0,1.0, 0.5); // Textfeld hat 50% Alpha -> sieht cool aus
        glBindTexture(GL_TEXTURE_2D,texPaintarea);
    }
    else
        glUniform4f(framecolor_loc,_BackgroundColor.r,_BackgroundColor.g,_BackgroundColor.b,_BackgroundColor.a);


    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);

    glDrawElements( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Diese Funktion ersetzt  RenderBottom und RenderHeader
// Der einzige unterschied war die Texture !!
void TextRender::RenderFrame(GLfloat x, GLfloat y, uint tex) {
    // Standard Masse der images !!
    GLfloat w = _Textfeld.w;
    GLfloat h = 16.0f;

    GLfloat vertices[6][4] = {
            { x,     y  - h,        0.0, 0.0 },
            { x,     y,             0.0, 1.0 },
            { x + w, y,             1.0, 1.0 },

            { x, y - h,             0.0, 0.0 }, // w muss weg für 6  uv = 0,0 !!
            { x + w, y,             1.0, 1.0 },
            { x + w, y - h,         1.0, 0.0 }
    };

    glUniform4f(framecolor_loc,1.0,1.0,1.0,1.0);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
    glBindTexture(GL_TEXTURE_2D,tex);
    glDrawElements( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// ---------------------------------------------------
// Render Function
// param in [x] - X Position in screencoords
// param in [y] - y Position in screnecoords
// ---------------------------------------------------
void TextRender::Render() {

    GLfloat _x = posX;
    GLfloat _y = posY;

    //projection =  glm::ortho(0.0f,static_cast<GLfloat>(_ResX), static_cast<GLfloat>(_ResY) , 0.0f);   //,  -1.0f, 1.0f);
    projection =  glm::orthoRH(0.0f,static_cast<GLfloat>(_ResX), static_cast<GLfloat>(_ResY), 0.0f,  -100.0f, 100.0f);


    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // Breite ermitteln:
    std::string::const_iterator c;
    GLfloat feldweite = 0.0f;
    GLfloat feldhoehe = 20.0f; // Standard höhe 16 Pixel
    GLfloat width = 0.0f;
    int count = 0;
    for ( uint i = 0; i < _StringList.size(); i ++ ) {
        for (c = _StringList[i].begin(); c != _StringList[i].end(); c++) {
            Character ch = Characters[*c];
            feldweite += static_cast<GLfloat> ( (ch.Advance >> 6) * _Scale);
        }
        count ++;

        if ( width < feldweite )
            width = feldweite;
        feldweite = 0.0f;
    }
    feldhoehe = feldhoehe * count * _Scale;

    _Textfeld.w = width * _Scale + _MarginLeft + _MarginRight;
    _Textfeld.h = feldhoehe;
    GLfloat newX;
    if ( _AlignRight )
         newX = _ResX - _Textfeld.w;
    else
        newX = _x;

    // --------------------------------
    // Erstmal alles fürs TextFenster
    //---------------------------------


    if (_HasTexture)
        currentshader =shader_textfeld ;
    else
        currentshader = shaderColorTextfeld;

    glUseProgram(currentshader);

    projection_loc = glGetUniformLocation(currentshader,"projection_textfeld");
    framecolor_loc = glGetUniformLocation(currentshader,"color");
    // IDentity
    glm::mat4 Model(1.0f);

    glm::mat4 mp = projection ;//* Model ;
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(mp)); // projection matrix im shader init.
  //  glUniform4f(framecolor_loc,_BackgroundColor.r,_BackgroundColor.g,_BackgroundColor.b,_BackgroundColor.a);


    if (_HasBackground ) {
        // ALle Buffers binden ....
        glBindVertexArray(_bgVAO);
        glBindBuffer(GL_ARRAY_BUFFER,_bgVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_bgEBO);

        RenderPaintarea(newX, _y - (16 - _MarginY*2), feldhoehe);

        // Alles Rendern
        if (_RenderHeader)
            RenderFrame(newX, _y - (16.0f - _MarginY*2), texHeadline );

        if (_RenderBottom)
            RenderFrame(newX, _y + feldhoehe, texBottom );
        // ... und aushängen
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    _x = newX + _MarginLeft;
    GLfloat startX  = _x;
    GLfloat row     = _y + 16.0f;//_MarginY;
    //--------------------
    // Text Rendern
    //--------------------
    glActiveTexture(GL_TEXTURE0);
    glUseProgram(shader2D);
    glBindVertexArray(_VAO);
    mv_projectloc = glGetUniformLocation(shader2D,"projection");
    uniform_colorloc   = glGetUniformLocation(shader2D,"col2D");

    //glm::mat4 Model(1.0f);
    glm::mat4 mvp = projection * Model ;

    glUniformMatrix4fv(mv_projectloc, 1, GL_FALSE, glm::value_ptr(mvp)); //projection));
    glUniform4f(uniform_colorloc,_TextColor.r, _TextColor.g, _TextColor.b, _TextColor.a);


    // Iterate through all characters
    // std::string::const_iterator c;

    for (uint i = 0; i < _StringList.size(); i++ ) {
        for (c = _StringList[i].begin(); c != _StringList[i].end(); c++)
        {
            Character ch = Characters[*c];

            GLfloat xpos = _x + ch.Bearing.x * _Scale;
            //GLfloat ypos = row - ((ch.Size.y - ch.Bearing.y) * _Scale) ;

            GLfloat ypos;
            ypos = row;
            ypos = row + ((ch.Size.y - ch.Bearing.y) * _Scale) ;

            GLfloat w = ch.Size.x * _Scale;
            GLfloat h = ch.Size.y * _Scale;
            // Update VBO for each character
            GLfloat vertices[6][4] = {
                { xpos,     ypos - h - 6.0f,   0.0, 0.0 },  // alles 16 war 6 !!
                { xpos,     ypos - 6.0f,       0.0, 1.0 },
                { xpos + w, ypos - 6.0f,       1.0, 1.0 },

                { xpos,     ypos - h - 6.0f,   0.0, 0.0 },
                { xpos + w, ypos - 6.0f,       1.0, 1.0 },
                { xpos + w, ypos - h - 6.0f,   1.0, 0.0 }



            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D,ch.TextureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, _VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
            glDrawElements( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            _x += (ch.Advance >> 6) * _Scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        _x =     startX;
        row +=  18.0f *_Scale; //  + bearingdiff ;  // 16
    }
    // Aufräumen
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    //glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
}
