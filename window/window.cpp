
#include "window.h"


Window::Window(int resx, int resy, Shader * sh) :
    Base2D(resx,resy,sh)
{

}

Window::Window(int resx, int resy,std::string path, Shader * sh) :
    Base2D(resx,resy,path, sh)
{


}

void Window::Render() {
    Base2D::Render();

}

void Window::OnClick() {}
