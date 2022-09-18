#include "base.h"

Base::Base()
{

}
Base::~Base() {}


//void Base::Render(){}

bool Base::intersect(int x, int y) {
    return  ( ((x > _Pos.x) && (x < _Pos.x + _Size.w) ) &&
              ((y > _Pos.y) && (y < _Pos.y + _Size.h)) ) ? true : false;
}


void Base::setWidth(int w) {
    _Size.w = w;
    calcDragBar();
}

int Base::Width(){
    return _Size.w;
}

int Base::Height() {
    return _Size.h;
}
void Base::setHeight(int h) {
    _Size.h = h;
    calcDragBar();
}

void Base::setSize(int w, int h) {
    _Size.w = w;
    _Size.h = h;
    calcDragBar();
}

void Base::setPos(int x, int y) {
    _Pos.x = x;
    _Pos.y = y;

    calcDragBar();
}

void Base::calcDragBar() {
    // -----------------------------------------------
    // Bereich für Dragging
    // -----------------------------------------------
    interSectHeadline.x  = _Pos.x;
    interSectHeadline.x1 = _Pos.x + _Size.w;
    interSectHeadline.y  = _Pos.y;
    interSectHeadline.y1 = _Pos.y + 40;
}

sPoint Base::Pos() {
    return _Pos;
}

bool Base::IsEnabled(){
    return _Enable;
}

glm::vec4 Base::color() { return  _Color; }

void Base::setColor(glm::vec4 col) {
    _Color = col;
}
void Base::setDisablecolor(glm::vec4 disCol) {
    _DisableColor = disCol;
}

void Base::disable(){
    _Enable = false;
}
void Base::enable(){
    _Enable = true;
}


//------------------------------------------------------------------------
//Draging
//------------------------------------------------------------------------
void Base::OnStartDrag(int mx, int my) {

    if ( ! _Dragging) {
        distX = mx - interSectHeadline.x;
        distY = _Pos.y - my;

        _Dragging = true;
    }
}

void Base::OnDrag(int mx, int my) {
    _Pos.x = mx - distX;
    _Pos.y = my + distY;
}

void Base::OnEndDrag(int mx, int my) {

    _Pos.x = mx - distX;
    _Pos.y = my + distY;
    _Dragging = false;
}
bool Base::IsDragging() {
    return  _Dragging;
}
