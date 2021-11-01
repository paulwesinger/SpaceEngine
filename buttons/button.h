#ifndef CBUTTON_H
#define CBUTTON_H

#include "../base2d/base2d.h"
#include "../colors/colorscheme.h"
#include "../textrenderer/textrender.h"
//#include "../defaults.h"


// -----------------------------------------------
// Base class for all kind of buttons
// derrived classes must overwrite Method Render()
// -----------------------------------------------

typedef struct {
    std::string path;
    int PosX;
    int PosY;
    int SizeX;
    int SizeY;
    int Enable;
    float ImageRed;
    float ImageGreen;
    float ImageBlue;
    float TextRed;
    float TextGreen;
    float TextBlue;
} sButtonStruct;

class CButton : public Base2D
{
public:
    CButton(int resx, int resy);
    CButton(int resx, int resy, std::string path, std::string text);
    ~CButton();

    // ********************************************
    // Look and feel
    // ********************************************
    // set
    void setText(std::string t);

    void setPos(int x, int y);
    void enable();
    void disable();

    int Height();
    int Width();

    std::string Text();
    bool Enabled();

    FP clickFunc;  // aufzurufende func für Buttonclick
    //  FPEnableBtn clickFuncEnable;
    void AddHandler(FP handler);
    //*********************************************
    // Virtuals
    // ********************************************
    virtual void Render() = 0;
    virtual void setbuttonColors(glm::vec3 imagecol, glm::vec3 textcol);
    virtual void setScale(float s = 1.0f) = 0;

    //EventHandling
    //virtual void OnClick() = 0 ;  // Muss überschrieben werden !!!!
    virtual void OnRelease() = 0;
    virtual void OnFocus();

    virtual void alignToSize(int w, int h);


protected:

    virtual void animateClick();
    virtual void releaseClick();

    bool _Enabled;
    std::string _Text;
    sPoint textPos;
    float _AlphaText;
    float _Alpha_Image;

    glm::vec3 _ImageCol;
    glm::vec3 _TextCol;

private:

    void init();

    CColorScheme colorscheme;
    sButtonScheme _ButtonColors; // die vecs mit den farben
};

// ----------------------------------------------------
// Text Button zur Verwendung:
// ----------------------------------------------------

class CTextButton: public CButton {
  public:

    CTextButton( int resx, int resy);
    CTextButton( int resx, int resy, std::string path, std::string text, sPoint pos);


    void setbuttonColors(glm::vec3 imagecol, glm::vec3 textcol) override;
    void setScale(float s) override;

    void Render()  override;
    void OnClick() override;
    void OnRelease() override;
protected:
    void setSize(int w, int h) override;
    void animateClick() override;
    void releaseClick() override;

    void setPos(int x, int y) override;
    void alignToSize(int w, int h) override;

    float _TextScale;
    TextRender * btnText;
};



// ----------------------------------------------------
// Image Button zur Verwendung:
// ----------------------------------------------------

class CImageButton: public CButton {
  public:

    CImageButton( int resx, int resy);
    CImageButton( int resx, int resy, std::string pathbg, std::string pathtext, sPoint pos);

    void setbuttonColors(glm::vec3 imagecol, glm::vec3 textcol) override;

    void Render()  override;
    void OnClick() override;
    void OnRelease() override;
protected:
    void setSize(int w, int h) override;
    void animateClick() override;
    void releaseClick() override;
    void setScale(float s) override;

    Base2D * textImage;
    void  setPos(int x, int y) override;

private:
    std::string _TextPath;


};


#endif // CBUTTON_H
