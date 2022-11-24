#ifndef CHECKBOX_H
#define CHECKBOX_H


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



class CheckBox : public Base2D
{
public:
    CheckBox(int resx, int resy, Shader * sh);
    CheckBox(int resx, int resy,sPoint p, sSize s, glm::vec4 labelcol, Shader * sh);
    CheckBox(int resx, int resy,std::string path, sPoint p, sSize s, glm::vec4 labelcol, Shader* sh);
    ~CheckBox() override;
    void Render() override;

    void showLabel (bool show);
    void setLabel(std::string label);
    void setChecked();
    TextRender * getLabelPtr();
    bool Checked();
    void OnClick() override;
    void AddHandler(FPB Handler);
protected:
    TextRender * textLabel;
    TextRender * _X;
    bool _Checked;
    bool _ShowLabel;
    FPB clickFunc;


private:
    glm::vec4 _LabelTextColor;

    sPoint _PosLabel;
    sPoint _PosCheck;

    sSize _SizeLabel;
    sSize _SizeCheck;

    Shader * glyphShader;

    void init();

    int resX;
    int resY;

};

#endif // CHECKBOX_H
