#include "colorscheme.h"

using namespace glm;

// --------------------------------------------
// RED : Fast schwarzer Background, dunkelgelber(goldener) Text.



CColorScheme::CColorScheme()
{
    init();

}

sButtonScheme & CColorScheme::setScheme(int which) {
    switch(which) {
        case DARK: return shemes[DARK]; break;
        case RED : return shemes[RED]; break;
        case BLUE: return shemes[BLUE]; break;
        case GREEN: return shemes[GREEN]; break;
        case YELLOW: return shemes[YELLOW]; break;
        case SYSTEM: return  shemes[SYSTEM]; break;
    default:
        return shemes[SYSTEM];
    }
}
void CColorScheme::init() {
    // --------------------------------------------------------------------------------
    shemes[DARK].text_click = vec4(0.27,0.27,0.27,1.0);

    shemes[DARK].text_enabled = vec4(0.97,0.75,0.07,1.0);            // Gold
    shemes[DARK].text_disabled = vec4(0.5,0.5,0.5,1.0);            // Gold

    shemes[DARK].text_hover = vec4(0.27,0.27,0.27,1.0);             // dunkel
    shemes[DARK].background_hover = vec4(0.97,0.75,0.7,1.0);

    shemes[DARK].background_enabled = vec4(0.27,0.27,0.27,1.0);     // Wie Qt Creator
    shemes[DARK].background_disabled = vec4(0.27,0.27,0.27,1.0);    // bleibt glecih
    shemes[DARK].background_click = vec4(0.97,0.75,0.7,1.0);    // bleibt glecih

    shemes[DARK].frame_disabled = vec4(0.5,0.5,0.5,1.0);    // bleibt gleich
    shemes[DARK].frame_enabled = vec4(0.97,0.75,0.07,1.0);    // bleibt gleich

    DarkSheme = shemes[DARK];
    // --------------------------------------------------------------------------------

    shemes[RED].text_click = vec4(0.27,0.27,0.27,1.0);

    shemes[RED].text_enabled = vec4(0.9,0.9,0.9,1.0);            // Gold
    shemes[RED].text_disabled = vec4(0.69,0.57,0.57,1.0);        // Gold

    shemes[RED].text_hover = vec4(0.27,0.27,0.27,1.0);             // dunkel
    shemes[RED].background_hover = vec4(1.0,0.48,0.27,1.0);

    shemes[RED].background_enabled = vec4(0.98,0.31,0.31,1.0);     // Wie Qt Creator
    shemes[RED].background_disabled = vec4(0.95,0.61,0.57,1.0);    // bleibt glecih
    shemes[RED].background_click = vec4(0.95,0.85,0.57,1.0);    // bleibt glecih

    shemes[RED].frame_disabled = vec4(0.69,0.57,0.57,1.0);    // bleibt gleich
    shemes[RED].frame_enabled = vec4(0.97,0.9,0.9,1.0);    // bleibt gleich

    // --------------------------------------------------------------------------------

    shemes[BLUE].text_click = vec4(0.27,0.27,0.27,1.0);

    shemes[BLUE].text_enabled = vec4(0.97,0.75,0.07,1.0);            // Gold
    shemes[BLUE].text_disabled = vec4(0.19,0.55,0.98,1.0);            // Gold

    shemes[BLUE].text_hover = vec4(0.19,0.27,0.98,1.0);             // dunkel
    shemes[BLUE].background_hover = vec4(0.19,0.90,0.08,1.0);

    shemes[BLUE].background_enabled = vec4(0.19,0.27,0.98,1.0);     // Wie Qt Creator
    shemes[BLUE].background_disabled = vec4(0.19,0.87,0.98,1.0);    // bleibt glecih
    shemes[BLUE].background_click = vec4(0.19,0.90,0.08,1.0);    // bleibt glecih

    shemes[BLUE].frame_disabled = vec4(0.19,0.55,0.98,1.0);    // bleibt gleich
    shemes[BLUE].frame_enabled = vec4(0.97,0.75,0.07,1.0);    // bleibt gleich

    // --------------------------------------------------------------------------------

    shemes[GREEN].text_click = vec4(0.27,0.27,0.27,1.0);

    shemes[GREEN].text_enabled = vec4(0.97,0.75,0.07,1.0);            // Gold
    shemes[GREEN].text_disabled = vec4(0.48,0.84,0.29,1.0);            // Hellgrün

    shemes[GREEN].text_hover = vec4(0.27,0.27,0.27,1.0);             // dunkel
    shemes[GREEN].background_hover = vec4(0.48,0.84,0.29,1.0);

    shemes[GREEN].background_enabled = vec4(0.37,0.92,0.08,1.0);     // Wie Qt Creator
    shemes[GREEN].background_disabled = vec4(0.16,0.40,0.03,1.0);    // bleibt glecih
    shemes[GREEN].background_click = vec4(00.27,0.27,0.27,1.0);    // bleibt glecih

    shemes[GREEN].frame_disabled = vec4(0.48,0.84,0.29,1.0);    // bleibt gleich
    shemes[GREEN].frame_enabled = vec4(0.97,0.75,0.07,1.0);    // bleibt gleich

    // --------------------------------------------------------------------------------

    shemes[YELLOW].text_click = vec4(0.33,0.33,0.33,1.0);

    shemes[YELLOW].text_enabled = vec4(0.33,0.33,0.22,1.0);            // Gold
    shemes[YELLOW].text_disabled = vec4(0.51,0.53,0.33,1.0);            // Hellgrün

    shemes[YELLOW].text_hover = vec4(0.33,0.33,0.33,1.0);             // dunkel
    shemes[YELLOW].background_hover = vec4(0.48,0.84,0.29,1.0);

    shemes[YELLOW].background_enabled = vec4(0.95,0.89,0.15,1.0);     // Wie Qt Creator
    shemes[YELLOW].background_disabled = vec4(0.77,0.74,0.32,1.0);    // bleibt glecih
    shemes[YELLOW].background_click = vec4(0.48,0.84,0.29,1.0);    // bleibt glecih

    shemes[YELLOW].frame_disabled = vec4(0.51,0.53,0.33,1.0);    // bleibt gleich
    shemes[YELLOW].frame_enabled = vec4(0.33,0.33,0.22,1.0);    // bleibt gleich

    // --------------------------------------------------------------------------------

    shemes[SYSTEM].text_click = vec4(0.33,0.33,0.33,1.0);

    shemes[SYSTEM].text_enabled = vec4(0.33,0.33,0.22,1.0);            // Gold
    shemes[SYSTEM].text_disabled = vec4(0.51,0.53,0.50,1.0);            // Hellgrün

    shemes[SYSTEM].text_hover = vec4(0.75,0.75,0.75,1.0);             // dunkel
    shemes[SYSTEM].background_hover = vec4(0.34,0.35,0.33,1.0);

    shemes[SYSTEM].background_enabled = vec4(0.76,0.77,0.74,1.0);     // Wie Qt Creator
    shemes[SYSTEM].background_disabled = vec4(0.76,0.77,0.74,1.0);    // bleibt glecih
    shemes[SYSTEM].background_click = vec4(0.76,0.77,0.74,1.0);    // bleibt glecih

    shemes[SYSTEM].frame_disabled = vec4(0.51,0.53,0.50,1.0);    // bleibt gleich
    shemes[SYSTEM].frame_enabled = vec4(0.33,0.33,0.22,1.0);    // bleibt gleich

}
