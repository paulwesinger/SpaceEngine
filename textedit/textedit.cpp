#include "textedit.h"
#include "../defaults.h"

TextEdit::TextEdit(int resx, int resy)
    :Base2D(resx,resy){
    resX = resx;
    resY = resy;

    _Pos.x = 100;
    _Pos.y = 100;
    _Size.w = 100;
    _Size.h = 50;

    textLabel = nullptr;
    editLabel = nullptr;

    _LabelTextColor = LABEL::COLOR_TEXT;
    _TextEditColor  = LABEL::COLOR_BACKGROUND;

    init();
}
TextEdit::TextEdit(int resx, int resy, sPoint p, sSize s, glm::vec4 labelcol, glm::vec4 editcol)
    :Base2D(resx,resy){

    resX = resx;
    resY = resy;
    _Pos    = p;
    _Size   = s;
    _LabelTextColor = labelcol;
    _TextEditColor  = editcol;

    textLabel = nullptr;
    editLabel = nullptr;

    init();


}
TextEdit::TextEdit(int resx, int resy,std::string path, sPoint p, sSize s, glm::vec4 labelcol, glm::vec4 editcol)
    :Base2D(resx,resy,path){

    Base2D::setPos(p.x,p.y);

    resX = resx;
    resY = resy;
    _Pos    = p;
    _Size   = s;
    _LabelTextColor = labelcol;
    _TextEditColor  = editcol;
    init();

}

TextRender* TextEdit::getTextPtr(){
    return editLabel;
}

TextRender* TextEdit::getLabelPtr(){
    return textLabel;
}

void TextEdit::setLabel(std::string  label){
    if (textLabel != nullptr)
        textLabel->setText(0, label);
}

void TextEdit::setText(std::string text) {
    if (editLabel != nullptr)
        editLabel->setText(0, text);
}
void TextEdit::Render() {
    Base2D::Render();

    if (textLabel != nullptr && _ShowLabel)
        textLabel->Render();

    if (editLabel != nullptr)
        editLabel->Render();

}

void TextEdit::showLabel(bool show){
    _ShowLabel = show;
}

void TextEdit::init() {

    _ShowLabel = true;

    textLabel = new TextRender(resX, resY, _PosLabel);
    _PosLabel.x = _Pos.x + LABEL::MARGIN_X;
    _PosLabel.y = _Pos.y + LABEL::MARGIN_Y;
    _SizeLabel.w = _Size.w / 2;

    _SizeLabel.h = textLabel->getTextAreaHeight();
    textLabel->SetScale(TEXT::SCALE_SMALL);
    textLabel->AddString("Test");
    textLabel->SetAlignRight(false);
    textLabel->setPos(_PosLabel);
    textLabel->SetTextColor(_LabelTextColor);
    // EditLabel:
    editLabel = new TextRender(resX, resY, _PosLabel);
    _PosText.x = _PosLabel.x + 100;// _Size.w / 2 ;
    _PosText.y = _Pos.y + LABEL::MARGIN_Y;
    _SizeText.w = _Size.w / 2 - 10 ;
    _SizeText.h = editLabel->getTextAreaHeight();
    editLabel->SetScale(TEXT::SCALE_SMALL);
    editLabel->AddString("<>");
    editLabel->SetAlignRight(false);
    editLabel->setPos(_PosText);
    editLabel->SetTextColor(_TextEditColor);
}
