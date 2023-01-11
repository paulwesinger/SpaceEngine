

#ifndef INITGL_H
#define INITGL_H

#include <cstdio>
#include <cstdlib>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <map>
#include <irrklang/irrKlang.h>
#include "logs/logs.h"
#include "utils/utils.h"
#include "shaders/shader.h"
#include "cube/cube.h"
#include "cube/colorcube.h"
#include "sphere/sphere.h"
#include "skybox/skybox.h"
#include "landscape/landscape.h"
#include "base2d/base2d.h"
#include "camera/camera.h"
#include "defines.h"
#include "fileutils/fileutil.h"
#include "objectclasses/object.h"
#include "projection/projection.h"
#include "textrenderer/textrender.h"
#include "baseobject/baseobject.h"
#include "menu/menu.h"
#include "meshobject/meshobject.h"
#include "objloader/objloader.h"
#include "textedit/textedit.h"
#include "buttons/button.h"
#include "lights/light.h"
#include "cockpit/cockpit.h"
#include "particleengine/partikelengine.h"
#include "3DLoader/load3ds.h"
#include "defaults.h"

// static flags for handler in derrived classes
extern bool _RenderSkybox;
extern bool _Animate;
extern bool _UseBlend;
extern bool _ShowCockpit;
extern bool _ShowPanel;   // DrawPanel für 2D

class InitGL {
public:

    InitGL( std::string titel = "OpenGL");
    InitGL(const InitGL& orig);

    void setRootPath(std::string path);
    // Create Context and Init SDL2
    bool InitSDL2();
    Shader * getShaderPtr();

    virtual void Run();
    virtual void Done();
    // Methode zum abbrechen
    void sdl_die( std::string msg);
    virtual ~InitGL();
    void showSkyBox();

    virtual void Prepare2D(); // Flags für Rendern einstellen
    virtual void Restore3D(); // Flags zurücksetzen

    // effects
    static void setFog(bool enable = false);

    void fogParam();

protected:
    std::vector<std::string> split(std::string const& input, std::string const& separator);
    //----------------------------------
    // Look and feel
    //----------------------------------
    virtual void Render(glm::mat4 cam);
    virtual void SetResolution(int resx,int resy);
    virtual bool HandleMessage();
    virtual void InitEngineObject();
    virtual void InitUserObjects();

    void SetClearColor(float r, float g, float b, float a);
    void setClearColor(float r, float g, float b);
    void toogleFullScreen();

    void LoadConfiguration();
    void InitFX();
    static void toggleAnimation();
    static void toogleCockpit();
    static void toggleBlend();
    static void togglePanel2D();
    static void toggleSkyBox();
    static bool toggleVal(bool val);

    // HandlerFuncs for Mouse
    virtual void OnMouseMove(int &x, int &y, uint32 buttonstate);
    virtual void OnLeftMouseButtonUp(int &x, int &y);
    virtual void OnLeftMouseButtonDown( int &x, int &y);

    //----------------------------------
    // Object creation
    // ---------------------------------
    void add2List(BaseObject * obj, ShaderType s);
    void add2Dobject(Base2D * obj);
    void addButton(CButton* obj);
    virtual void ShowFramesPerSec();
    virtual void ShowCameraPos();

    bool hasSkyBox();
    void setHasSkybox(bool enable);

    //----------------------------------
    // Main Menu
    // ---------------------------------
    CMenu* MainMenu;
    bool showMenu;


    // Flags for effects:
    bool _Fog;
    bool _HasSkyBox;
    bool _UseBlinn;
    void safeDelete(BaseObject * bo);

    CSphere *sphere1;
    CSphere *lightSource;   // Damit wir wissen wo die ichtquekke wirjkich  ist

    //LandScape * land;

    Base2D * base2d;
    Camera * camera;  // = View !!
    SkyBox * skybox;

    fileUtil * filestream = nullptr;
    Projection * projection;
    TextRender * MousePositions;
    TextRender * _Frames;
    light * ambientLight = nullptr;

    // Cockpit:
    Cockpit * cockpit;
    PartikelEngine * PE;


    // Liste für 3D objekte
    std::vector<BaseObject*> list3D;

    // Liste für die 2D Objekte
    std::vector<Base2D *> objects2D;
    // Eine Button liste
    std::vector<CButton*>  buttons;

    //Liste für Textfelder
    std::vector<TextRender*> textfields;

    // Members for navigating with the  mouse...
    MOUSE _Mouse;
    float MouseResX;
    float MouseResY;
    uint32  _MouseButtons;

/*
    irrklang::ISoundEngine * soundengine;
    irrklang::ISoundEngine * soundengine1;
    irrklang::ISoundEngine * soundengine2;
    irrklang::ISoundEngine * soundengine3;
    irrklang::ISound       * _Sound;
    bool _HasSound;
*/
    // Test Shader
    Shader * shader;
    GLuint glasshader;
    GLuint cubeshaderprog_color;
    GLuint cubeshaderprog_tex;
    GLuint cubeshaderprog_normals;
    GLuint cubeshaderprog_color_normal;
    GLuint sphereshader_color;
    GLuint lighttexture_shader;
    // Derzeit noch nicht verwendbar !!!
    GLuint line2DShader;

    GLuint textfeldshader, textshader;
    ShaderType _CurrentShader;

    bool _ShaderChanged;
    bool _FullScreen ;
    bool _QuitGame;

    //Flags for overrides
    bool _ShowFramesPerSecond   = false;
    bool _ShowMousePositions     = false;
    bool _ShowCameraPos         = false;

    uint32_t _Elapsed;


    // Global Resolution vars
    int _ResX;
    int _ResY;
    int _FramerateOut;
    float _CameraSpeed;

    std::string caption;
    FLOAT4 _ClearColor;


    const std::string MAIN_CFG = PATH::ROOT +"config/Engine/engine.cfg";
    const std::string SPACE = " ";

    const int  SD_WIDTH     =  1600;
    const int  SD_HEIGHT    =  1200;
    const int  FULLSCREEN_WIDTH = 3200;//1680.0f//1920.0f
    const int  FULLSCREEN_HEIGHT = 1800;//1050.0f//1200.0f


    SDL_Event       _Event;
    bool _LockClick = false;
  //  C3DSLoad * load3DS;

private:


    void InitUtils();  // Fileutils,logs ,etc....
    void InitShaders();
    void InitMatrices();
    bool initSoundMachine();
    void DeleteUtils();
    void DeleteMatrices();
    void DeleteShaders();
    void PrintDisplayModes();

    SDL_Window * window;
    SDL_GLContext maincontext;

    SDL_DisplayMode DesktopDisplayMode;
    SDL_DisplayMode newDisplayMode;
};

// -------------------------------------
// Abgeleitete Testklsse
// --------------------------------------




#endif // INITGL_H
