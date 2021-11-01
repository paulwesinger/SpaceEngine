#include "button.h"
#include "../logs/logs.h"
#include "../defaults.h"
#include "../utils/utils.h"

CButton::CButton(int resx, int resy) :
    Base2D(resx,resy) {

    init();
}
CButton::CButton(int resx, int resy, std::string path, std::string text) :
    Base2D(resx, resy,path){
    _Text = text;
    init();
}

void CButton::init() {

     _ButtonColors = colorscheme.setScheme(DARK);

    setWidth(BUTTON::DEFAULT_WIDTH);
    setHeight(BUTTON::DEFAULT_HEIGHT);
    textPos.x = _Pos.x + BUTTON::X_MARGIN;
    textPos.y = _Pos.y + BUTTON::Y_MARGIN;

    _AlphaText    = TEXT::ALPHA_ENABLED;
    _Alpha_Image  = BUTTON::ALPHA_IMAGE_ENABLED;

    _ImageCol = BUTTON::COLOR_DEFAULT_IMAGE;
    _TextCol  = BUTTON::COLOR_DEFAULT_TEXT;
}
CButton::~CButton() {

}

// ----------------------------------------------
// Look and feel
// ----------------------------------------------

void CButton::setText(std::string t) { _Text = t; }

void CButton::enable() {
    Base2D::disable();
    _Enabled = true;
    _AlphaText   = TEXT::ALPHA_ENABLED;
    _Alpha_Image = BUTTON::ALPHA_IMAGE_ENABLED;
}

void CButton::disable() {
    Base2D::disable();
    _Enabled = false;
    _AlphaText    = TEXT::ALPHA_DISABLED;
    _Alpha_Image  = BUTTON::ALPHA_IMAGE_DISABLED;
}

std::string CButton::Text() {return  _Text; }
bool CButton::Enabled() { return _Enabled; }


// Handler Func
void CButton::AddHandler(FP handler) {
    clickFunc = handler;
}

void CButton::animateClick(){

}
void CButton::releaseClick() {}

void CButton::alignToSize(int w, int h) {}

void CButton::setbuttonColors(glm::vec3 imagecol, glm::vec3 textcol) {
    _ImageCol = imagecol;
    _TextCol  = textcol;

    Base2D::setColor(glm::vec4(imagecol,_Alpha_Image));
}

void CButton::setScale(float s) {}

int CButton::Height(){
    return Base2D::Height();
}

int CButton::Width(){
    return Base2D::Width();
}

void CButton::setPos(int x, int y){
    Base2D::setPos(x,y);

}
// -----------------------------------------------
// Event Handling
// -----------------------------------------------
/*
void CButton::OnClick() {
    //clickFunc();
}  // Must be overwritten
*/
void CButton::OnRelease(){}

void CButton::OnFocus() {
    loginfo("OnFocus","CButton::OnFocus");
}

void CButton::Render( ) {}


//--------------------------------------------------
// Defaullt Buttons for use
// -------------------------------------------------

CTextButton::CTextButton( int resx, int  resy) :
    CButton(resx, resy)

{
    _Text = "NO";
    _Pos.x = 0;
    _Pos.y = 0;
    btnText = new TextRender(resx, resy);
    textPos.x = _Pos.x + BUTTON::X_MARGIN;
    textPos.y = _Pos.y + BUTTON::Y_MARGIN;
}

CTextButton::CTextButton(int resx, int resy, std::string path, std::string text, sPoint pos):
    CButton(resx, resy, path,text){

    _Pos = pos;

    textPos.x = _Pos.x + BUTTON::X_MARGIN;
    textPos.y = _Pos.y + BUTTON::Y_MARGIN;

    setText(text);
    btnText = new TextRender(resx, resy);
    btnText->AddString(text);
    btnText->setPos(textPos);
    btnText->SetTextColor(glm::vec4(_TextCol,1.0));
    btnText->SetHasBottom(false);
    btnText->SetHasHeader(false);
    btnText->SetHasBackground(false);
    btnText->SetHasTexture(false);
    btnText->SetAlignRight(false);

}

void CTextButton::animateClick() {
    if (btnText != nullptr) {
        sPoint p;
        p = btnText->Pos();
        p.x -= 2;
        p.y -= 2;

        btnText->setPos(p);
    }
}

void CTextButton::releaseClick() {
    if (btnText != nullptr) {
        sPoint p;
        p = btnText->Pos();
        p.x += 2;
        p.y += 2;
        btnText->setPos(p);
    }
}

void CTextButton::setbuttonColors(glm::vec3 imagecol, glm::vec3 textcol)  {

    CButton::setbuttonColors(imagecol, textcol);
    btnText->SetTextColor(glm::vec4(textcol,1.0));
}

void CTextButton::alignToSize(int w, int h){
    if (btnText != nullptr)
        btnText->alignToRectSize(w,h);
}

void CTextButton::setScale(float s) {
    _TextScale = s;
    if (btnText)
        btnText->SetScale(_TextScale);
}

// overritten

void CTextButton::setPos(int x, int y) {
    Base2D::setPos(x,y);

    textPos.x = _Pos.x + BUTTON::X_MARGIN;
    textPos.y = _Pos.y + BUTTON::Y_MARGIN;

    sPoint p;
    p.x = (int) textPos.x;
    p.y = (int) textPos.y;
    btnText->setPos(p);
}

void CTextButton::setSize(int w, int h) {
    Base2D::setSize(w, h);

    // Todo : setSize in TextRender

}

void CTextButton::Render() {


    Base2D::setColor(glm::vec4(1.0,1.0,1.0,_Alpha_Image));
    Base2D::Render();
    btnText->Render();

    //textImage->Base2D::setColor(glm::vec4(1.0,1.0,1.0,_AlphaText));
    //textImage->Base2D::Render();
}

void CTextButton::OnClick() {
    clickFunc();
    animateClick();
}
void CTextButton::OnRelease(){
    releaseClick();
}



//--------------------------------------------------
// Image Button for use
// -------------------------------------------------

CImageButton::CImageButton( int resx, int  resy) :
    CButton(resx, resy)

{
    textPos.x = _Pos.x + BUTTON::X_MARGIN;
    textPos.y = _Pos.y + BUTTON::Y_MARGIN;
    // init stuff
    textImage = new Base2D(resx, resy, "images/Add.png");
    textImage->setPos(0,0);

}

CImageButton::CImageButton(int resx, int resy, std::string pathbg, std::string pathtext, sPoint pos):
    CButton(resx, resy, pathbg,""){

    _TextPath = pathtext;
    _Pos = pos;

    textPos.x = _Pos.x + BUTTON::X_MARGIN;
    textPos.y = _Pos.y + BUTTON::Y_MARGIN;

    sPoint p;
    p.x = (int) textPos.x;
    p.y = (int) textPos.y;

    textImage = new Base2D(resx, resy,_TextPath);
    textImage->setColor(glm::vec4(BUTTON::COLOR_DEFAULT_TEXT,_AlphaText));
    textImage->setPos(0,0);
    // init stuff
}

void CImageButton::animateClick() {


    if (textImage != nullptr) {
        sPoint p;

        p = textImage->Pos();
        textImage->setPos(p.x-2, p.y-2);
    }


}

void CImageButton::releaseClick() {


    if (textImage != nullptr) {
        sPoint p = textImage->Pos();

        textImage->setPos(p.x+2, p.y+2);
    }

}

void CImageButton::setbuttonColors(glm::vec3 imagecol, glm::vec3 textcol)  {

    CButton::setbuttonColors(imagecol, textcol);
    textImage->setColor(glm::vec4(textcol,_AlphaText));
}
// overritten

void CImageButton::setPos(int x, int y) {
    Base2D::setPos(x,y);
    textImage->setPos(_Pos.x,_Pos.y);
}

void CImageButton::setScale(float s) {}
void CImageButton::setSize(int w, int h) {
    Base2D::setSize(w, h);
    if (textImage != nullptr) {
        textImage->setSize(w, h);
    }
}

void CImageButton::Render() {


    Base2D::setColor(glm::vec4(1.0,1.0,1.0,_Alpha_Image));
    Base2D::Render();

    textImage->Base2D::setColor(glm::vec4(1.0,1.0,1.0,_AlphaText));
    textImage->Base2D::Render();
}

void CImageButton::OnClick() {
    clickFunc();
    animateClick();
}
void CImageButton::OnRelease(){
    releaseClick();
}








