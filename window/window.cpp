
#include "window.h"


Window::Window(int resx, int resy) :
    Base2D(resx,resy)
{

}

Window::Window(int resx, int resy,std::string path) :
    Base2D(resx,resy,path)
{

}



void Window::Render() {}

void Window::OnClick() {}
