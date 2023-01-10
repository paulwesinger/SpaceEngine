#ifndef CENGINE_H
#define CENGINE_H

#include <vector>

#include "../initgl.h"
#include "../buttons/button.h"
#include "../textrenderer/textrender.h"
#include "../fileutils/fileutil.h"
#include "../textedit/textedit.h"
#include "../checkbox/checkbox.h"
#include "../defines.h"
#include "../defaults.h"
#include "../controllcontainer/controllcontainer.h"
#include "../menu/menu.h"
#include "../window/window.h"



const std::string BUTTONS_CFG  = PATH::ROOT + "config/Buttons/";
const std::string OBJECT3D_CFG = PATH::ROOT + "config/3DObjects/";
const std::string COCKPIT_CFG  = PATH::ROOT + "config/3DObjects/Cockpits/";
const std::string SPHERE_CFG   = PATH::ROOT + "config/3DObjects/TexturedSpheres/";



const int CFG_BUTTON_SIZE = 11;
const int CFG_3D_SIZE = 18;
const int CFG_SPHERE_SIZE = 26;

const glm::vec4 BTN_ENABLE = glm::vec4(0.2, 0.2, 0.2, 1.0);
const glm::vec4 BTN_DISABLE = glm::vec4(0.2, 0.2, 0.2, 0.3);

const int MENU_SPACER = 10;


//--------------------------------------
// Look and feel
//--------------------------------------
const int BTN_WIDTH = 150;
const int BTN_HEIGHT = 30;


static CButton* butn0;
static CButton* butn1;
static CButton* butn2;


class CEngine : public InitGL
{
public:
    CEngine(std::string titel = "OpenGL 4.5 Engine");
    ~CEngine();
    void Run() override;
    void Done() override;
    bool HandleMessage() override;



protected:
    void loadButtons();
    void Render(glm::mat4 cam)  override;
    // Lists for all objects:
    std::vector<std::string> btnList;
    std::vector<std::string> object2DList;
    std::vector<std::string> object3DTexturedList;
    std::vector<std::string> object3DColoredList;
    std::vector<std::string> object3DLandscapeList;
    std::vector<std::string> objectCockpitList;
    std::vector<std::string> objectTexturedSpheresList;

    CControllContainer *con1;
    CControllContainer *con2;

    CButton * toogleSkyBoxBtn;

    static void funcFog();
    static void funcToogleSkybox();
    static void functoogleAnimation(bool checked);
    static void functoogleBlend(bool checked);
    static void functoogleCockpit(bool checked);
    static void DrawPanel();

 private:

    void InitButtons();
    void Init2D();
    void Init3D();
    void initMenu();
    void initLandscape();

    // virtuelle functions
    void ShowFramesPerSec() override;
    void ShowCameraPos() override;

    bool initButtonStruct(sButtonStruct & bs,std::vector<std::string> cfg);
    bool init3DStruct(s3DStruct & d3s, std::vector<std::string> &cfg);
    bool initLandscape(sLandscape &ls, std::vector<std::string> &cfg);
    bool initSphereStruct(sSphereStruct & sSphere, std::vector<std::string> &cfg);

    bool loadSpheres();
    bool loadTexturedCubes();
    bool loadColorCubes();
    bool loadLandscape();
    bool loadCockpits();
    //----------------------------------------------------------------
    // Menu controlls
    //----------------------------------------------------------------
    TextEdit * txtFrameperSec;
    CheckBox * checkBoxAnimation;
    CheckBox * checkBoxBlending;
    CheckBox * checkBoxCockpit;

    // Label für CameraPos :
    TextEdit * cameraX;
    TextEdit * cameraY;
    TextEdit * cameraZ;
    TextEdit * camerayaw;
    TextEdit * cameradirZ;
    TextEdit * cameradirX;

    // Toolboxes, sonstige Fenster
    Window * testToolBox;


    std::string &getValueItem(std::string &s, std::string erasestring);
    TextRender * textrenderer;
    fileUtil * fu;
    //-----------------------------------------------------------------
    //tamplate
    //-----------------------------------------------------------------
    void setupTemplate(int i);
};


#endif // CENGINE_H
