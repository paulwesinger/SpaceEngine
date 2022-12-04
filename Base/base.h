#ifndef BASE_H
#define BASE_H


#include "../defines.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Base
{
public:
    Base();
    ~Base();


    virtual void Render() = 0;

    virtual void OnStartDrag(int mx, int my);
    virtual void OnDrag(int mx, int my);
    virtual void OnEndDrag(int mx, int my);


    virtual bool intersect(int x, int y);
    virtual void setWidth( int w);
    virtual void setHeight( int h);
    virtual void setSize( int w, int h);
    virtual void setPos(int x, int y);
    virtual void setColor(glm::vec4 col);
    virtual void calcDragBar();


    virtual int Height();
    virtual int Width();
    virtual void disable();
    virtual void enable();
    virtual bool IsDragging();
    glm::vec4 color();
    bool IsEnabled();
    sPoint Pos();
    void setDisablecolor(glm::vec4 disCol);

protected:
    sPoint _Pos;
    sSize  _Size;

    glm::vec4 _Color;
    glm::vec4 _DisableColor;
    bool _Enable;
    int _ResX;
    int _ResY;


    // hlpvars for drag
    int distX;
    int distY;
    sRect  interSectHeadline;
    bool   _Dragging;
};




#endif // BASE_H
