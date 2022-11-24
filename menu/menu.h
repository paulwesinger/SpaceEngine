#ifndef CMENU_H
#define CMENU_H

#include "../textrenderer/textrender.h"
#include "../controllcontainer/controllcontainer.h"
#include "../buttons/button.h"
#include "../checkbox/checkbox.h"
#include "../base2d/base2d.h"
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "../defines.h"

#include <vector>


const int MENU_WIDTH  = 190;
const int MENU_HEIGHT = 800;

typedef struct {
    sRect Pos;
    TextRender * text;
} sMenuStruct ;


class CMenu
{
public:
    CMenu(int resX, int resY,Shader * sh);
    CMenu(int resX, int resY, int w, int h,Shader * sh);
    CMenu(int resX, int resY, int w, int h, glm::vec4 bg, glm::vec4 fg,Shader * sh);
    CMenu(int resX, int resY, int px, int py, int w, int h, glm::vec4 bg, glm::vec4 fg, Shader *sh);

    void Render();
    void setMenuHeader(std::string name);
    void setActive(bool active);
    bool Active();

    //----------------------------------------
    // container functions
    //----------------------------------------
    void addConatiner( CControllContainer* con);
    void addButton(CControllContainer * con, CButton * btn);
    void addTextItem(CControllContainer * con, std::string text);
  //  void addCheckBox(CControllContainer * con, CheckBox * cb);

    sPoint Pos();
    int Width();
    int Height();
    int CurrentY();

    void AlignLeft();
    void AlignRight();

    std::vector<sMenuStruct> menuItems;
    std::vector<CControllContainer *> containerList;
protected:

    Base2D * menuBackground;

    glm::vec4 backgroundColor;
    glm::vec4 foregroundColor;

    int posX;  // absolute zum bildschirm
    int posY;
    int width;
    int height;

    bool alignright;
    bool alignleft;

private:
    void init();

    Shader * shader;
    int _currentY; //hilfsvariable für nächste freie y-positon im Menu - relativ zu bildschirm
    int _resX;
    int _resY;
    bool _Active;

};

#endif // CMENU_H
