#ifndef TEXTRENDER_H
#define TEXTRENDER_H

/*
 * File:   TextRender.h
 * Author: paul
 *
 * Created on 23. Juni 2019, 11:23
 */

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdio>
#include <string>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "../shaders/shader.h"
#include "../defines.h"




const std::string GNU_DEFAULT_FONT = "/usr/share/fonts/gnu-free/FreeSans.ttf";
const std::string GNU_DEFAULT_FONT_BOLD = "/usr/share/fonts/gnu-free/FreeSansBold.ttf";

const std::string GNU_DEFAULT_OBLIQUE_FONT = "/usr/share/fonts/gnu-free/FreeSansOblique.ttf";
const std::string GNU_DEFAULT_OBLIQUE_FONT_BOLD = "/usr/share/fonts/gnu-free/FreeSansBoldOblique.ttf";



struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    FT_Pos     Advance;    // Offset to advance to next glyph
    GLuint     Height;
};

struct sTextfeld{
    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
};

class TextRender {
public:
    TextRender(int resx, int resy,Shader * sh);
    TextRender(int resx, int resy, sPoint pos, Shader * sh);
    TextRender(int resx, int resy, sPoint pos,std::string imagetextfield,Shader * sh);
    TextRender(int resx, int resy, sPoint pos,std::string imagehead, std::string imagetextfield,Shader * sh);
    TextRender(int resx, int resy, sPoint pos,std::string imagehead, std::string imagetextfield,std::string imagebottom, Shader * sh);

    TextRender(const TextRender& orig);
    virtual ~TextRender();
    virtual void OnStartDrag(int mx, int my);
    virtual void OnDrag(int mx, int my);
    virtual void OnEndDrag(int mx, int my);

    bool Init(int resx,int resy);
    void SetHasHeader(bool hasheader);
    void SetHasBottom(bool hasbottom);
    void SetHasBackground(bool hasbg);
    void setImagePath(std::string path);

    void SetTextColor(glm::vec4 col);
    void SetBackgroundColor(glm::vec4 col);
    void SetHasTexture(bool hasTex);
    void AddString(std::string s);
    void SetAlignRight(bool align);
    void SetScale(GLfloat scale);

    void SetColorShader(GLuint s);
    void SetTextureShader(GLuint s);
    void SetGlyphShader(GLuint s);
    void SetFont(std::string s);

    uint GetStringCount();
    int GetTextAreaHeight();
    int GetHeight();
    int GetWidth();

    void AlignToRectSize(int w, int h);
    void SetText(uint index, std::string newString);  // starts qt 0 !!
    void SetPos(sPoint pos);
    sPoint Pos();
    bool Intersect(int x, int y);
    bool IsDragging();
    void CalcSize(int &weite, int &height);
    void Render();

protected:
    void RenderPaintarea(GLfloat x, GLfloat y, GLfloat height);
    void RenderFrame(GLfloat x, GLfloat y, uint tex);  // Header und/oder Bottom

private:

    bool _RenderHeader;
    bool _RenderBottom;
    bool _HasBackground;
    bool _HasTexture;
    bool _AlignRight;

    bool _FAILED;

    GLfloat _Scale;

    glm::vec4 _TextColor;
    glm::vec4 _BackgroundColor;

    int _ResX;
    int _ResY;

    sPoint _Pos;

    GLfloat posX;
    GLfloat posY;

    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;

    // Buffers und arrays für Background
    GLuint _bgVAO;
    GLuint _bgVBO;
    GLuint _bgEBO;

    Shader * shader;
    // ints for shader returns
    int vs;
    int fs;

    // -----------------------
    // Shader für das Textfeld
    //------------------------
    int vs_textfeld;
    int fs_textfeld;
    uint _TextureShader,_GlyphShader,_ColorShader,_CurrentShader;

    //GLuint _TextShader, _TextFeldShader, _CurrentShader;

    GLint mv_projectloc;
    GLint uniform_colorloc;
    // uniformlocations in textfeldshader --> nur einmal setzen ,
    // für alle 3 Renderer(Headline Paintarea, Bottom)
    GLuint projection_loc, framecolor_loc;

    glm::mat4 projection;

    //Texturen für Textfeldrahmen
    unsigned int texHeadline, texBottom, texPaintarea;
    // ------------------------------
    // Includes und libs für Freetype2
    FT_Library ft;
    FT_Face face;
    std::string _Font;
    // Einige Felder für look and feel:
    FT_UInt _Pixelsize;
    GLfloat _MarginLeft,_MarginRight, _MarginY;

    std::map<GLchar, Character> Characters;
    //Hilfsfunktion zum einlesen der 5 Texturen für Textfeld
    bool GenTextfeldSegment(std::string image, unsigned int &tex);

    sTextfeld _Textfeld;
    std::vector<std::string> _StringList;

    std::string _PathHeadLine;
    std::string _PathTextField;
    std::string _PathBottomLine;
private:

    // hlpvars for drag
    int distX;
    int distY;
    sRect  interSectHeadline;
    bool   _Dragging;

};


#endif // TEXTRENDER_H
