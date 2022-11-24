#include "menu.h"
#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../defaults.h"



CMenu::CMenu(int resX, int resY, Shader * sh) {
    _resY = resY;
    _resX = resX;

    shader = sh;

    posX = 0;
    posY = 0;

    width =  MENU_WIDTH;
    height = MENU_HEIGHT;

    backgroundColor = glm::vec4(0.0,0.0,0.0,1.0);
    foregroundColor = glm::vec4(1.0,1.0,1.0,1.0);

    init();
}

CMenu::CMenu(int resX, int resY, int w, int h, Shader * sh) {
    _resY = resY;
    _resX = resX;

    shader  = sh;

    posX = 0;
    posY = 0;

    width =  w;
    height = h;

    backgroundColor = glm::vec4(0.0,0.0,0.0,1.0);
    foregroundColor = glm::vec4(1.0,1.0,1.0,1.0);

    init();
}

CMenu::CMenu(int resX, int resY, int w, int h, glm::vec4 bg, glm::vec4 fg, Shader * sh) {

    _resY = resY;
    _resX = resX;
    _currentY = 0;

    shader = sh;
    posX = 0;
    posY = 0;

    width =  w;
    height = h;

    backgroundColor = bg;
    foregroundColor = fg;

    init();
}

CMenu::CMenu(int resX, int resY, int px, int py, int w, int h, glm::vec4 bg, glm::vec4 fg, Shader * sh) {

    _resY = resY;
    _resX = resX;
    _currentY = 0;

    shader = sh;

    posX = px;
    posY = py;

    width =  w;
    height = h;

    backgroundColor = bg;
    foregroundColor = fg;

    init();
}

void CMenu::init() {

    menuBackground = new Base2D(_resX, _resY, shader);
    menuBackground->setPos(posX, posY);
    menuBackground->setSize(width, height);
    menuBackground->setColor(backgroundColor);

    _Active = true;
}

void CMenu::setActive(bool active) {
    _Active = active;
}

bool CMenu::Active() {
    return _Active;
}

sPoint CMenu::Pos() {
    sPoint p;
    p.x = posX;
    p.y = posY;
    return p;
}

int CMenu::Width() {
    return width;
}

int CMenu::Height() {
    return height;
}

int CMenu::CurrentY(){
    return _currentY;
}

void CMenu::Render() {
    menuBackground ->Render();
    if (! containerList.empty() ) {
        for(uint i=0; i < containerList.size(); i++) {

            if ( ! containerList.at(i) ->buttons.empty()) {
                for (uint j=0; j < containerList.at(i)->buttons.size(); j++){
                    containerList.at(i)->buttons.at(j) ->Render();
                }
            }
            if ( ! containerList.at(i) ->controlls2D.empty() ) {
                for (uint j=0; j < containerList.at(i)->controlls2D.size(); j++){
                    containerList.at(i)->controlls2D.at(j) ->Render();
                 }
            }
        }
    }

}

void CMenu::setMenuHeader(std::string name) {
    sMenuStruct ms;
    ms.text = new TextRender(_resX,_resY, shader);
    ms.text->AddString(name);

    _currentY += ms.text->GetTextAreaHeight();
}

void CMenu::addButton(CControllContainer* con, CButton *btn) {

    if ( con == nullptr  || btn == nullptr )
        return;

    con->addButton(btn);
}

void CMenu::addConatiner(CControllContainer *con) {

    if ( con == nullptr )
        return;
    containerList.push_back(con);
    _currentY += con->Dimensions().h + 1;
    loginfo("Add Controllcontainer to Menu .... Done"  ,"CMenu::addContainer");

}

void CMenu::addTextItem(CControllContainer *con, std::string text) {
    if ( con == nullptr)
        return;

    // Hier eigentlich header text..! container anpassen !!
}


void CMenu::AlignLeft() {

    alignleft = true;
    alignright = false;
}

void CMenu::AlignRight() {

    alignright = true;
    alignleft = false;
}
