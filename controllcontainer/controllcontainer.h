#ifndef CCONTROLLCONTAINER_H
#define CCONTROLLCONTAINER_H

#include <vector>
#include "../base2d/base2d.h"
#include "../baseobject/baseobject.h"
#include "../buttons/button.h"
#include "../textrenderer/textrender.h"
#include "../defines.h"
#include "../shaders/shader.h"



const int SPACER = 10;

// Container Class für
// 2D Steuerelemente(Buttons ,...
class CControllContainer
{
public:
    CControllContainer(Shader * sh);
    CControllContainer(Shader * sh, int px=0, int py=0, int w=100, int h=100);
    ~CControllContainer();

    bool removeContainer(CControllContainer *container);
    void rename(std::string theNewName);

    void enableChilds();
    void disableChilds();
    void disableControll(Base2D * con);
    void enableControll(Base2D * con);

    bool addControll2D(Base2D *control);
    bool addControll3D(BaseObject * baseobject);
    bool addButton(CButton * btn);
    bool addText(std::string text,int resx, int resy);
    bool addSpacer();

    void setPos(sPoint pos);
    void setDimensions(sSize size);

    sSize Dimensions();
    sPoint Pos();
    sPoint NextControllPos();

    std::vector<Base2D *> controlls2D;
    std::vector<BaseObject*> controlls3D;
    std::vector<CButton *> buttons;
    std::vector<TextRender*> texts;


private:

    void releaseConterItems();

    std::string _Name;

    int _Height; // errechnete höhe
    int _Width;
    int _CurrentY; //position für nächstes element
    int _CurrentX;

    sSize _Dimensions; // von user seite
    sPoint _Pos; // absoluter wert


    Shader * shader;


};

#endif // CCONTROLLCONTAINER_H
