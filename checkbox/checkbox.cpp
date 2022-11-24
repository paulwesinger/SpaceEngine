#include "checkbox.h"
#include "../defaults.h"

CheckBox::CheckBox(int resx, int resy, Shader * sh) :
    Base2D(resx,resy,sh)
{
    glyphShader = sh;
    init();
}

CheckBox::CheckBox(int resx, int resy,sPoint p, sSize s, glm::vec4 labelcol, Shader * sh):
        Base2D(resx,resy,sh)
{
    resX = resx;
    resY = resy;
    _Pos    = p;
    _Size   = s;
    _LabelTextColor = labelcol;
    textLabel = nullptr;
    _X = nullptr;

    glyphShader = sh;
    init();
}

CheckBox::CheckBox(int resx, int resy,std::string path, sPoint p, sSize s, glm::vec4 labelcol, Shader * sh) :
    Base2D(resx,resy,path,sh)
{
    resX = resx;
    resY = resy;
    _Pos    = p;
    _Size   = s;
    _LabelTextColor = labelcol;
     textLabel = nullptr;
    _X = nullptr;
    glyphShader = sh;
    init();
}

CheckBox::~CheckBox() {
    if (textLabel != nullptr)
        delete textLabel;
}

void CheckBox::init() {
    _ShowLabel = true;

    _PosLabel.x = _Pos.x + LABEL::MARGIN_X;
    _PosLabel.y = _Pos.y + LABEL::MARGIN_Y;
    textLabel = new TextRender(resX, resY, _PosLabel,glyphShader);

    _SizeLabel.w = 20;
    _SizeLabel.h = 20;

    _SizeLabel.h = textLabel->GetTextAreaHeight();
    textLabel->SetScale(TEXT::SCALE_SMALL);
    textLabel->AddString("<>");
    textLabel->SetAlignRight(false);
    textLabel->SetPos(_PosLabel);
    textLabel->SetTextColor(_LabelTextColor);

    _PosCheck.x = _PosLabel.x + 100;// _Size.w / 2 ;
    _PosCheck.y = _Pos.y + LABEL::MARGIN_Y;

    _X = new TextRender(resX,resY,_PosCheck,glyphShader);

    _SizeCheck.w = _Size.w / 2;
    _SizeCheck.h = 20;
    _Checked = true;
    _X->SetScale(TEXT::SCALE_SMALL);
    _X->AddString("X");
    _X->SetAlignRight(false);
    _X->SetPos(_PosCheck);
    _X->SetTextColor(_LabelTextColor);
}

void CheckBox::Render() {
    Base2D::Render();

    if (textLabel != nullptr && _ShowLabel)
        textLabel->Render();

    if (_X != nullptr)
        _X->Render();
}

void CheckBox::OnClick(){
  setChecked();
  clickFunc(_Checked);
}

TextRender* CheckBox::getLabelPtr(){
    return textLabel;
}

void CheckBox::showLabel (bool show) {
    _ShowLabel = show;
}

void CheckBox::setLabel(std::string label) {
    if (textLabel != nullptr)
        textLabel->SetText(0, label);
}

void CheckBox::setChecked() {

    _Checked = ! _Checked;
    if (_Checked )
        _X-> SetText(0,"X");
    else
        _X->SetText(0," ");
}

void CheckBox::AddHandler(FPB Handler) {
    clickFunc = Handler;
}

bool CheckBox::Checked() {
    return _Checked;
}
