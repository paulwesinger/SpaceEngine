#ifndef CCOLORSCHEME_H
#define CCOLORSCHEME_H

#include <glm/vec4.hpp>
#include "../defines.h"

struct sPANELSCHEME {
    glm::vec4 background;
    glm::vec4 frame;
} ;
typedef struct  {
    glm::vec4 background_enabled;
    glm::vec4 background_disabled;
    glm::vec4 background_hover; // Mouse over button but no click
    glm::vec4 background_click;

    glm::vec4 text_enabled;
    glm::vec4 text_disabled;
    glm::vec4 text_hover;
    glm::vec4 text_click;
    glm::vec4 frame_enabled;
    glm::vec4 frame_disabled;

} sButtonScheme;
// ------------------------------------
// add here additional schemes
// ------------------------------------



class CColorScheme
{
public:
    CColorScheme();
    sButtonScheme &setScheme(int which);

private:
    sButtonScheme shemes[MAX_SCHEMES];
    sButtonScheme DarkSheme;


    void init();

    sButtonScheme currentScheme;


};

#endif // CCOLORSCHEME_H
