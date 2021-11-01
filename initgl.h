

#ifndef INITGL_H
#define INITGL_H




#include <cstdio>
#include <cstdlib>
#include <string>


#include <GL/glew.h>
//#include <glad.h>



//#include <glm/mat4x4.hpp>
//#include "glm/gtc/matrix_transform.hpp"

#include <SDL2/SDL.h>
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

const std::string MAIN_CFG = "../SpaceEngine/config/Engine/engine.cfg";
const std::string SPACE = " ";


typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
    // use for colors too..
}GLFLOAT4;


// static flags for handler in derrived classes
static bool renderSkybox;
static bool _Animate;


class InitGL {
public:
    InitGL( std::string titel = "OpenGL");
    InitGL(const InitGL& orig);
    // Create Context and Init SDL2
    bool InitSDL2();

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

    void SetClearColor(float r, float g, float b, float a);
    void setClearColor(float r, float g, float b);
    void toogleFullScreen();

    void LoadConfiguration();
    void InitFX();
    static void stopAnimation();


    // HandleInput wird wahrscheinlich überflussig....
    virtual int HandleInput(SDL_Event e , uint &mox, uint &moy);

    // .... ersetzt durch HandleEvent und die virtuellen Handler dazu
    virtual uint HandleEvent(SDL_Event e);
    // HandlerFuncs for Mouse
    virtual void OnMouseMove(int &x, int &y, uint buttonstate);
    virtual void OnLeftMouseButtonClick(int &x, int &y);
    virtual void OnLeftMouseButtonUp(int &x, int &y);

    //----------------------------------
    // Object creation
    // ---------------------------------
    void add2List(BaseObject * obj, ShaderType s);
    void add2Dobject(Base2D * obj);
    void addButton(CButton* obj);
    virtual void ShowFramesPerSec(uint32 sec);
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

    void safeDelete(BaseObject * bo);

    //CMeshObject *me;
    //COBJLoader * objLoader;

    CSphere *sphere1;
    CSphere *lightSource;   // Damit wir wissen wo die ichtquekke wirjkich  ist

    //LandScape * land;

    Base2D * base2d;
    Camera * camera;  // = View !!
    SkyBox * skybox;

    fileUtil * filestream = nullptr;
    Projection * projection;
    TextRender * textrender;
    TextRender * _Frames;
    light * ambientLight = nullptr;
    // Liste für 3D objekte
    std::vector<BaseObject*> list3D;

    // Liste für die 2D Objekte
    std::vector<Base2D *> objects2D;
    // Eine Button liste
    std::vector<CButton*>  buttons;


    SDL_Event e;
    // Members for navigating with the  mouse...
    MOUSE _Mouse;
    float MouseResX;
    float MouseResY;

    irrklang::ISoundEngine * soundengine;
    irrklang::ISoundEngine * soundengine1;
    irrklang::ISoundEngine * soundengine2;
    irrklang::ISoundEngine * soundengine3;

    irrklang::ISound       * _Sound;
    bool _HasSound;

    // Test Shader
    Shader * shader;
    GLuint cubeshaderprog_color;
    GLuint cubeshaderprog_tex;
    GLuint cubeshaderprog_normals;
    GLuint cubeshaderprog_color_normal;
    GLuint sphereshader_color;
    ShaderType _CurrentShader;
    bool _ShaderChanged;

    bool _FullScreen ;
    // Global Resolution vars
    int _ResX;
    int _ResY;
    int _FramerateOut;
    float _CameraSpeed;

    std::string caption;

    GLFLOAT4 _ClearColor;


private:

    void InitEngineObject();
    void InitUtils();  // Fileutils,logs ,etc....
    void InitShaders();
    void InitMatrices();
    bool initSoundMachine();
    void DeleteUtils();
    void DeleteMatrices();
    void DeleteShaders();

    MOUSE convertMouse(int x, int y);

    SDL_Window * window;
    SDL_GLContext maincontext;

    SDL_DisplayMode DesktopDisplayMode;
    SDL_DisplayMode newDisplayMode;

};

// -------------------------------------
// Abgeleitete Testklsse
// --------------------------------------




#endif // INITGL_H
