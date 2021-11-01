#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "../base2d/base2d.h"
#include "../textrenderer/textrender.h"
#include "../logs/logs.h"
#include "../shaders/shader.h"
#include "../utils/utils.h"
#include "../defines.h"
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>



class TextEdit : public Base2D
{
public:
    TextEdit(int resx, int resy);
    TextEdit(int resx, int resy,sPoint p, sSize s, glm::vec4 labelcol, glm::vec4 editcol);
    TextEdit(int resx, int resy,std::string path, sPoint p, sSize s, glm::vec4 labelcol, glm::vec4 editcol);

    void Render();
    void showLabel (bool show);
    void setLabel(std::string label);
    void setText(std::string text);
    TextRender * getLabelPtr();
    TextRender * getTextPtr();

protected:
    TextRender * textLabel;
    TextRender * editLabel;

private:
    glm::vec4 _LabelTextColor;
    glm::vec4 _TextEditColor;

    sPoint _PosLabel;
    sPoint _PosText;

    sSize _SizeLabel;
    sSize _SizeText;


    void init();
    bool _ShowLabel;

    int resX;
    int resY;

};

#endif // TEXTEDIT_H
