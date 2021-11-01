#include "loadimage.h"
#include "../logs/logs.h"

CLoadImage::CLoadImage(string  path)
{
    _Path = path;
}

CLoadImage::~CLoadImage(){}

SDL_Surface * CLoadImage::getSurface(string  path,string obj){

    SDL_Surface * surf = IMG_Load( path.c_str() );
    if ( surf ) {
      //  loginfo("Succes:  Image " + path + " loaded",obj);
        return surf;
    }
    else {
        surf = loadStandardSurface();
        logwarn("Warning: Image " + path + " not loaded ! created a template image ! Please Check Path.", obj);
        return  surf;
    }

}

SDL_Surface * CLoadImage::loadStandardSurface(){

    return IMG_Load(STANDARDIMAGE.c_str());
}
