#include "initgl.h"
#include "Cad/cad2d.h"


/*
 * File:   Init3D.cpp
 * Author: paul
 *
 * Created on 17. Mai 2018, 21:11
 */

#include "initgl.h"
//#include "vecmath/vecmath.h"
#include <vector>
//#include "3DLoader/load3ds.h"

// Res for windowed Mode

#define SD_WIDTH    1600
#define SD_HEIGHT   1200
#define FULLSCREEN_WIDTH  1680.0f//3200//1680.0f//1920.0f
#define FULLSCREEN_HEIGHT 1050.0f//1800//1050.0f//1200.0f

const std::string PATH_HEADLINE     = "../SpaceEngine/images/darkgray.png";
const std::string PATH_TEXTFIELD    = "../SpaceEngine/images/Textfeld.png";
const std::string PATH_BOTTOM       = "../SpaceEngine/images/Bottom.png";

using namespace irrklang;

InitGL::InitGL (const std::string titel){

    caption = titel;
    window = nullptr;
    maincontext = nullptr;

    _Frames = nullptr;
    _FramerateOut = 0;

    _Mouse.lastx = 0;
    _Mouse.lasty = 0;
    _Mouse.x     = 0;
    _Mouse.y     = 0;

    sphere1 = NULL;
    lightSource = NULL;
    skybox  = NULL;
    base2d  = NULL;
   // land = nullptr;

    cockpit = nullptr;
    PE      = nullptr;

    MousePositions = NULL;
   // soundengine = NULL;
    projection = nullptr;

    MainMenu = nullptr;
    showMenu = false;
    _ShaderChanged = false;

    _CameraSpeed = 1.0f;

    LoadConfiguration();
    InitUtils();
    InitMatrices();
    _HasSound = initSoundMachine();
    InitFX();

    // Irrklan init
 //   soundengine = createIrrKlangDevice();
 //   if ( soundengine )
 //       loginfo(" SoundEngine created ","InitGL::InitGL");
}

InitGL::InitGL(const InitGL& orig) {
}

InitGL::~InitGL() {

    // Alten Videomode wiederherstellen
    SDL_SetWindowDisplayMode(window,&DesktopDisplayMode);

//    if (soundengine)
//        soundengine->drop();

    safeDelete(sphere1);
    safeDelete(lightSource);
    //safeDelete(land);

    if ( skybox != NULL)
        delete skybox;
    if (base2d != NULL  )
        delete base2d;
//    if (cockpit != NULL)
//        delete cockpit;

    if (ambientLight != nullptr)
        delete  ambientLight;

    DeleteUtils();
    DeleteMatrices();
    DeleteShaders();
}

void InitGL::DeleteShaders() {
    glDeleteProgram(cubeshaderprog_color);
    glDeleteProgram(cubeshaderprog_tex);
    glDeleteProgram(sphereshader_color);
    glDeleteProgram(cubeshaderprog_color_normal);

}

void InitGL::safeDelete(BaseObject * bo) {
    if (bo != NULL) {
        delete bo;
        bo = NULL;
    }
 }

//------------------------------------------
//  Abstracts Render
// -----------------------------------------
void InitGL::Render(glm::mat4 cam) {

    if ( skybox != nullptr )
        skybox->Draw(cam);

    // Hier noch zusätzliche virtuelle Renderer (objecte, und so weiter!
}

void InitGL::showSkyBox() {

}


bool InitGL::hasSkyBox() { return _HasSkyBox; }
void InitGL::setHasSkybox(bool enable) { _HasSkyBox = enable; }

void InitGL::LoadConfiguration(){


    _FullScreen = false;
    _ResX = SD_WIDTH;
    _ResY = SD_HEIGHT;

    fileUtil * fu = new fileUtil();
    std::vector<std::string> enginecfg;
    bool ok = fu->readLine(MAIN_CFG,enginecfg);

    if (ok) {
        for (uint i = 0; i< enginecfg.size(); i++) {

            std::vector<std::string> parts = split(enginecfg.at(i), SPACE);
            if ( ! parts.empty()) {

                if ( parts.at(0) == "FullScreen") {
                    if (parts.size() > 1) {  // wenigstens 2 einträge:
                        _FullScreen = (StringToInt(parts.at(1)) == 1 ? true : false);
                        if (_FullScreen)
                            loginfo("Schalte auf Fullscreen.......Done");
                        else
                            loginfo("Schalte auf Window-Mode.......Done");
                    }
                }
                else if ( parts.at(0) == "Resolution") {
                    if (parts.size() > 2) {  // wenigstens 3 einträge:
                        _ResX = StringToInt(parts.at(1));
                        _ResY = StringToInt(parts.at(2));
                        loginfo("Setting Resolution " +parts.at(1) + "x" + parts.at(2) + ".......Done");
                    }
                    else
                        logwarn("Warnung: konnte Resolution nich lesen -> verwende Default 1920x1200");
                }
            }
        }
    }
    else
        logwarn("Konnte keine .cfg Datei finden ","CEngine::LoadConfiguration");

}

std::vector<std::string> InitGL::split(std::string const& input, std::string const& separator = " ")
{
  std::vector<std::string> result;
  std::string::size_type position, start = 0;

  while (std::string::npos != (position = input.find(separator, start)))
  {
    result.push_back(input.substr(start, position-start));
    start = position + separator.size();
  }

  result.push_back(input.substr(start));
  return result;
}


//------------------------------------------
// effects
//------------------------------------------
void InitGL::InitFX(){

}


// fog
void InitGL::fogParam(){
    float col[4] = {0.5f,0.5f,0.5f,1.0f};
    glFogi(GL_FOG_MODE,GL_LINEAR);
    glFogfv(GL_FOG_COLOR ,col);
    glFogf(GL_FOG_DENSITY, 0.75f);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
    glFogf(GL_FOG_END, 5.0f);               // Fog End Depth
    glEnable(GL_FOG);

}
void InitGL::setFog(bool enable) {
        //Shader use forfogging
}




// ******************************************
// Utils
// ------------------------------------------
void InitGL::InitUtils() {
    filestream = new fileUtil();
    if (filestream == NULL) {
        logwarn ("Konnte Util FileStream nicht erstellen !!","InitGL::InitUtils");
    }
    else
        loginfo("Erstelle FileUtil...... DEone","InitGL::InitUtils");
}

void InitGL::InitShaders() {
    //================================================================
    //Test für CustomShader

    shader = new Shader();
    int vs;
    int fs;

    // Vertex Shader
    // ------------------------------------------------------------------------
    std::string v_source ="../SpaceEngine/ShaderSources/cubevertexshader.vex";
    vs = shader ->compileVertexShaderFromFile(v_source,filestream);
    //Fragment Shader Color
    v_source ="../SpaceEngine/ShaderSources/colorshader.frg";
    fs = shader ->compileFragmentShaderFromFile(v_source,filestream);

    // ColorCubeShader
    loginfo("Erstelle Cube Color Shader.................done");
    shader->CreateCustomShader(cubeshaderprog_color);
    shader->AttachCustomShader(cubeshaderprog_color,vs);
    shader->AttachCustomShader(cubeshaderprog_color,fs);
    shader->CreateCustomProgram(cubeshaderprog_color);
    glDetachShader(cubeshaderprog_color,vs);
    glDetachShader(cubeshaderprog_color,fs);
    logEmptyLine();

    // Fragment Shader Texture
    v_source ="../SpaceEngine/ShaderSources/cubefragmentshaderMulti.frg";
    fs = shader ->compileFragmentShaderFromFile(v_source,filestream);
    //Texture CubeShader
    loginfo("Erstelle Cube Texture Shader ..............done");
    shader->CreateCustomShader(cubeshaderprog_tex);
    shader->AttachCustomShader(cubeshaderprog_tex,vs);
    shader->AttachCustomShader(cubeshaderprog_tex,fs);
    shader->CreateCustomProgram(cubeshaderprog_tex);
    glDetachShader(cubeshaderprog_tex,vs);
    glDetachShader(cubeshaderprog_tex,fs);


    // Shader für lightning
    loginfo("Erstelle Cube Lightning Shader ..............done");
    v_source ="../SpaceEngine/ShaderSources/cubevertexnormalshader.vex";
    vs = shader ->compileVertexShaderFromFile(v_source,filestream);
    //Fragment Shader Color
    v_source ="../SpaceEngine/ShaderSources/cubefragmentshaderMultinormals.frg";
    fs = shader ->compileFragmentShaderFromFile(v_source,filestream);
    shader->CreateCustomShader(cubeshaderprog_normals);
    shader->AttachCustomShader(cubeshaderprog_normals,vs);
    shader->AttachCustomShader(cubeshaderprog_normals,fs);
    shader->CreateCustomProgram(cubeshaderprog_normals);
    glDetachShader(cubeshaderprog_normals,vs);
    glDetachShader(cubeshaderprog_normals,fs);

    // Shader für colorlightning
    loginfo("Erstelle Cube Color Light Shader ..............done");
    v_source ="../SpaceEngine/ShaderSources/vertexnormalcolorshader.vex";
    vs = shader ->compileVertexShaderFromFile(v_source,filestream);
    //Fragment Shader Color
    v_source ="../SpaceEngine/ShaderSources/fragmentnormalcolorshader.frg";
    fs = shader ->compileFragmentShaderFromFile(v_source,filestream);
    shader->CreateCustomShader(cubeshaderprog_color_normal);
    shader->AttachCustomShader(cubeshaderprog_color_normal,vs);
    shader->AttachCustomShader(cubeshaderprog_color_normal,fs);
    shader->CreateCustomProgram(cubeshaderprog_color_normal);
    glDetachShader(cubeshaderprog_color_normal,vs);
    glDetachShader(cubeshaderprog_color_normal,fs);

    // Shader für Texture lightning
    loginfo("Erstelle Lightning Shader ..............done");
    v_source ="../SpaceEngine/ShaderSources/VertexTextureLightShader.vex";
    vs = shader ->compileVertexShaderFromFile(v_source,filestream);
    //Fragment Shader Color
    v_source ="../SpaceEngine/ShaderSources/FragmentTextureLightShader.frg";
    fs = shader ->compileFragmentShaderFromFile(v_source,filestream);
    shader->CreateCustomShader(lighttexture_shader);
    shader->AttachCustomShader(lighttexture_shader,vs);
    shader->AttachCustomShader(lighttexture_shader,fs);
    shader->CreateCustomProgram(lighttexture_shader);
    glDetachShader(lighttexture_shader,vs);
    glDetachShader(lighttexture_shader,fs);

    // Shader für Glas
    loginfo("Erstelle Glas Shader ..............done");
    v_source ="../SpaceEngine/ShaderSources/glasshader.vex";
    vs = shader ->compileVertexShaderFromFile(v_source,filestream);
    //Fragment Shader Color
    v_source ="../SpaceEngine/ShaderSources/glasshader.frg";
    fs = shader ->compileFragmentShaderFromFile(v_source,filestream);
    shader->CreateCustomShader(glasshader);
    shader->AttachCustomShader(glasshader,vs);
    shader->AttachCustomShader(glasshader,fs);
    shader->CreateCustomProgram(glasshader);
    glDetachShader(glasshader,vs);
    glDetachShader(glasshader,fs);

    _CurrentShader = ShaderType::LIGHT_SHADER;
    // ========================================================================

}

void InitGL::DeleteUtils() {
    if ( filestream != NULL) {
        delete filestream;
        loginfo("Deleted filestream","InitGL::DeleteUtils");
    }
}

void InitGL::DeleteMatrices() {
    if (projection != NULL) {
        delete projection;
        loginfo("Delete Prokjection Matrix Class","InitGL::DeleteMatrtices");
    }
}

// ******************************************
// MAtrices
// ------------------------------------------
void InitGL::InitMatrices() {
    projection = new Projection(0,_ResX,0,_ResY,0.01f,1000.0f);
    if (projection != NULL) {
        loginfo("Created Procjection Class","InitGL::InitMatrices");
    }
}

// ******************************************
// Heier der graphische Teil
// ------------------------------------------
bool InitGL::InitSDL2()  {


    if (  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
    {
            logwarn("Konnte SDL nicht initialisieren ! " + (std::string) SDL_GetError());
            return(false);
    }
    atexit(SDL_Quit);

    printf("Init success \n");
    SDL_GL_LoadLibrary(NULL);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    int numDisplaymodes = SDL_GetNumDisplayModes(0);
    loginfo("Num Display modes: " + IntToString(numDisplaymodes), "InitGL::Init");

    // Alle Display modes auflisten:


     for(int j = 0; j < SDL_GetNumVideoDisplays(); j++)
     {
        for (int i = 0; i < numDisplaymodes; i++ ) {
            SDL_DisplayMode dpm;
            SDL_GetDisplayMode(j,i,&dpm);
            std::string w = IntToString(dpm.w);
            std::string h = IntToString(dpm.h);
            std::string index =IntToString(i);
            try {

                // todo: Pixelformat auswerten
                loginfo("Display : " + IntToString(j) + "  Resolution Mode[" + index+ "] : " + w + "x" + h ,"InitGL::Init");
            }
            catch ( ...) {
                logwarn("Konnte mode[" + index + "] nicht ermitteln");
            }

        }
     }
    SDL_GetDesktopDisplayMode(0, &DesktopDisplayMode );

//    _ResX = FULLSCREEN_WIDTH;
//    _ResY = FULLSCREEN_HEIGHT;

    if ( _FullScreen) {


        window = SDL_CreateWindow(
                caption.c_str(),
                0, //SDL_WINDOWPOS_UNDEFINED,
                0, //SDL_WINDOWPOS_UNDEFINED,
                _ResX,_ResY,
                //SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL
                SDL_WINDOW_OPENGL
            );
        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);

    }
    else {

            _ResX = SD_WIDTH;
            _ResY = SD_HEIGHT;
            window = SDL_CreateWindow(
                caption.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                _ResX,_ResY,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
            );

    glViewport(0,0,_ResX, _ResY);
}



    if ( window == nullptr)  {
        sdl_die("Konnte Fenster nicht erzeugen");
        return false;
    }

    maincontext = SDL_GL_CreateContext(window);
    if ( ! maincontext) {
        sdl_die (" Konnte Context nicht erzeugen ");
        return false;
    }

    printf(" Geladene OpenGL version :");

    // Alles Ok ,checken was initialisiert ist :
    printf("Vendor :  %s\n",glGetString(GL_VENDOR));
    printf("Renderer  %s\n",glGetString(GL_RENDERER));
    printf("Version   %s\n",glGetString(GL_VERSION));


       GLenum err = glGetError();
       switch (err){
           case GL_NO_ERROR         :   loginfo (" Kein Fehler ","Base2D Render");  break;
           case GL_INVALID_ENUM     :   loginfo ("Invalid Enum","Base2D Render");   break;
           case GL_INVALID_VALUE    :   loginfo ("Invalid Value","Base2D REnder");  break;
           case GL_INVALID_OPERATION:   loginfo ("Invalid operation","Base2D Render"); break;
           case GL_INVALID_FRAMEBUFFER_OPERATION: loginfo ("Invalid Framebuffer Operation","Base2D Render"); break;
           case GL_OUT_OF_MEMORY    :   loginfo("Out of Memory","Base2D Render"); break;
           case GL_STACK_UNDERFLOW  :   loginfo ("Stack UNDERFLOW","Base2D Render"); break;
           case GL_STACK_OVERFLOW   :   loginfo ("Stack Overflow","Base2D Render"); break;
           default: loginfo("Undefined");
       }

    //loginfo("Erstelle Viewport " + IntToString(_ResX) + " x " + IntToString(_ResY),"InitGL::InitEngineObject");
    //glViewport(0,0, _ResX , _ResY );

    glewExperimental = GL_TRUE;
    glewInit();
    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    newDisplayMode.w = _ResX;
    newDisplayMode.h = _ResY;
    newDisplayMode.format = SDL_PIXELFORMAT_RGBX8888;


    //if (_FullScreen)
    SDL_SetWindowDisplayMode(window,&newDisplayMode);  // Only in fullscreen available

     // Testweise Displaymode ermitteln
    SDL_DisplayMode current;
    int error = SDL_GetCurrentDisplayMode(1, &current);
    if ( error == 0) {
       printf ("InitGL -- WindowSize:  %i x %i h \n",current.w,current.h);
    }
    else
        printf ("InitGL -- RES_X,RES_Y :  %i x %i h \n",_ResX,_ResY);

    MouseResX = (float)_ResX / (float)current.w;
    MouseResY = (float)_ResY / (float)current.h;

    InitEngineObject();


    // --------------------------------
    // Test Loader:
    //---------------------------------

    //me = new CMeshObject();
    //me->Load3DSMesh("Meshes/spaceship.3ds");

    //objLoader = new COBJLoader("Meshes/Quad.obj");

    //int errorid = objLoader->LoadOBJ();

    //logwarn(" OBJLoader return ID: " + IntToString(errorid));


    return true;
}

void InitGL::setClearColor(float r, float g, float b) {
    _ClearColor.x = r;
    _ClearColor.y = g;
    _ClearColor.z = b;
    _ClearColor.w = 1.0f;
    glClearColor(_ClearColor.x, _ClearColor.y, _ClearColor.z, _ClearColor.w);
}


void InitGL::SetClearColor(float r, float g, float b, float a) {
    _ClearColor.x = r;
    _ClearColor.y = g;
    _ClearColor.z = b;
    _ClearColor.w = a;
    glClearColor(_ClearColor.x, _ClearColor.y, _ClearColor.z, _ClearColor.w);
}

void InitGL::InitEngineObject() {
// ===============================================================
// Hier werden alle Objeckte initialisiert
// ===============================================================

    loginfo("Setze ClearColor auf Hell Blau ...... done","InitGL::InitEngineObject");
    setClearColor(0.57f,0.72f,0.92f);
    // ---------------------------------------
    // Camera View
    // ---------------------------------------
    loginfo("Erstelle Camera Objekt","InitGL::InitEngineObject");
    camera = new (Camera);
    loginfo("Erstelle Camera Objekt ...... done","InitGL::InitEngineObject");

    // ---------------------------------------
    // Light init
    //----------------------------------------
    ambientLight = new light;
    ambientLight->setColor(glm::vec3(1.0,1.0,1.0));
    ambientLight->setPos(glm::vec3(0.0,20.0,0.0));


    loginfo("Erstelle Standard Ambientes Licht ","InitGL::InitEngineObjects");

    // ---------------------------------------
    // Skybox ,objects init.
    // ---------------------------------------
    loginfo("Erstelle Standard SkyBox \"Dessert\" ........","InitGL::InitEngineObject");
    skybox = new SkyBox(projection->GetPerspective());
    std::vector<std::string> faces;

    faces.push_back("../SpaceEngine/skybox/desert/desert_lf.tga");
    faces.push_back("../SpaceEngine/skybox/desert/desert_rt.tga");
    faces.push_back("../SpaceEngine/skybox/desert/desert_up.tga");
    faces.push_back("../SpaceEngine/skybox/desert/desert_dn.tga");
    faces.push_back("../SpaceEngine/skybox/desert/desert_ft.tga");
    faces.push_back("../SpaceEngine/skybox/desert/desert_bk.tga");
    skybox -> Load(faces);
    loginfo("Erstelle Skybox ........Done","InitGL::InitEngineObject");

    loginfo("===========================");
    loginfo("Erstelle Shaders...........");
    loginfo("===========================");
    InitShaders();
    loginfo("..... done all");
    loginfo("============================");

    //================================
    // Init 2D Objects
    // ===============================

    logimage("Erstelle Text Renderer.....");
    sPoint p;
    p.x =   100;
    p.y =   400;

    MousePositions = new TextRender(_ResX, _ResY, p,PATH_HEADLINE, PATH_TEXTFIELD);

    MousePositions->SetTextShader(textshader);
    MousePositions->SetTextfeldShader(textfeldshader);

    MousePositions->AddString("Das ist die 1. Zeile");
    MousePositions->AddString("Das ist die 2. Zeile");
    MousePositions->AddString("Das ist die 3. Zeile");

    MousePositions->SetHasBottom(true);
    MousePositions->SetHasHeader(true);
    MousePositions->SetHasBackground(true);
    MousePositions->SetHasTexture(true);
    MousePositions->SetAlignRight(false);

    textfields.push_back(MousePositions);

    //========================================
    // Init 3D Objects
    //========================================

    loginfo("Erstelle 3D Objects .........");
    loginfo("Erstelle cube 1 - 3......done");

    // Liste mit Texture pfaden erstellen

    std::vector<std::string> cubeimages;
    fileUtil fu;
    // Texture loading
    bool texturesok;

    // Sphere
    loginfo("=============================");
    loginfo("Erstelle Sphere .........done");
    loginfo("=============================");
    cubeimages.push_back("../SpaceEngine/images/world.png");
    sphere1  = new CSphere(glm::vec3(6.0,5.0,-12.0),glm::vec4(1.0,0.0,0.0,0.2), projection->GetPerspective(),15,(GLfloat)4.0,shader);
    sphere1->addTexture(cubeimages,"InitGL::Sphere");
    cubeimages.clear();

    //-----------------------------------------
    // Lightsource as a spere
    //-----------------------------------------
    loginfo("Erstelle LichtQuelle als sphere....","InitGL::InitEngineObjects");
    lightSource = new CSphere(ambientLight->getPos(),glm::vec4(0.0,0.0,1.0,0.5),projection->GetPerspective(),18,(GLfloat)2.0,shader );
    lightSource->SetFrontFace(GL_CW);
    //Texture loading
    cubeimages.clear();
    texturesok =  fu.readLine("../SpaceEngine/config/cube2textures.cfg",cubeimages);
    if (texturesok)
        lightSource->addTexture(cubeimages,"Ad glob to lightsource");
    else
        logwarn("Init::Sphere1 konnte Textures nicht laden ! ","InitGL::Init::cube2::addTexture");
    cubeimages.clear();

    sphere1->initShader(COLOR_SHADER,cubeshaderprog_color);
    sphere1->initShader(TEXTURE_SHADER,cubeshaderprog_tex);
    sphere1->initShader(LIGHT_SHADER, cubeshaderprog_normals);
    sphere1->initShader(LIGHT_COLOR_SHADER, cubeshaderprog_color_normal);
    sphere1->initShader(GLASS_SHADER,glasshader);
    sphere1->setActiveShader(LIGHT_SHADER);
    //sphere1->setGlasShader(true);
    sphere1->addLight(ambientLight);

    lightSource->initShader(COLOR_SHADER,cubeshaderprog_color);
    lightSource->initShader(TEXTURE_SHADER,cubeshaderprog_tex);
    lightSource->initShader(LIGHT_SHADER, cubeshaderprog_normals);
    lightSource->initShader(LIGHT_COLOR_SHADER, cubeshaderprog_color_normal);
    lightSource->initShader(GLASS_SHADER,glasshader);
    lightSource->setActiveShader(LIGHT_SHADER);


    loginfo("--------------------------------------------");
    loginfo("Erstelle Cokpit ","InitGL::InitEngineObjects");
    loginfo("--------------------------------------------");

    cockpit = new Cockpit(projection->GetPerspective(),camera->GetPos());

    logwarn("Cokpit angelegt, Mesh wird in CEngine zugewiesen  !!", "IniEngineObjects");
    loginfo("Done 3D Objects .............");

    /*
    PE = new PartikelEngine(projection->GetPerspective(),ShaderType::LIGHT_TEXTURE_SHADER);
    PE->setShader(ShaderType::COLOR_SHADER,cubeshaderprog_color);
    PE->setShader(ShaderType::GLASS_SHADER,glasshader);
    PE->setShader(ShaderType::LIGHT_COLOR_SHADER,cubeshaderprog_normals);
    PE->setShader(ShaderType::LIGHT_SHADER,cubeshaderprog_tex);
    PE->setShader(ShaderType::LIGHT_TEXTURE_SHADER,lighttexture_shader);
    PE->setShader(ShaderType::TEXTURE_SHADER,cubeshaderprog_tex);
    PE->setEmissionTime(500); //ms
    PE->init();
*/


    logwarn("Partikelengine mit 100 Elementen !!", "IniEngineObjects");
    loginfo("Done 3D Objects .............");
}

// --------------------------------------------
// Adding's
// --------------------------------------------
void InitGL::add2List(BaseObject *obj, ShaderType s) {

    obj->initShader(COLOR_SHADER,cubeshaderprog_color);
    obj->initShader(TEXTURE_SHADER,cubeshaderprog_tex);
    obj->initShader(LIGHT_SHADER, cubeshaderprog_normals);
    obj->initShader(LIGHT_COLOR_SHADER, cubeshaderprog_color_normal);
    obj->initShader(GLASS_SHADER,glasshader);
    obj->setActiveShader(s);
    obj -> SetProjection(projection->GetPerspective());

    obj->addLight(ambientLight);
    list3D.push_back(obj);
}

void InitGL::add2Dobject(Base2D *obj) {
    objects2D.push_back(obj);
}

void InitGL::addButton(CButton* obj) {
    buttons.push_back(obj);
}

void InitGL::toogleFullScreen (){
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window,IsFullscreen ? 0 : FullscreenFlag);

    if (FullscreenFlag ) {

        //_ResX = FULLSCREEN_WIDTH;
        //_ResY = FULLSCREEN_HEIGHT;

        glViewport(0,0,FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT);//FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT);


    }
    else {
     //   _ResX = SD_WIDTH;
     //   _ResY = SD_HEIGHT;
        glViewport(0,0,_ResX, _ResY);
    }
}

void InitGL::ShowFramesPerSec(uint32 sec){

}

void InitGL::ShowCameraPos() {
}

void InitGL::toggleAnimation() {
    _Animate = toggleVal(_Animate);
}

void InitGL::toogleCockpit() {
    _ShowCockpit = toggleVal(_ShowCockpit);
}

void InitGL::toggleBlend() {
    _UseBlend = toggleVal(_UseBlend);
}
void InitGL::togglePanel2D() {
    showPanel = toggleVal(showPanel);
}

bool InitGL::toggleVal(bool val){
    return ! val;
}

bool InitGL::initSoundMachine() {
  //  soundengine = irrklang::createIrrKlangDevice();
  //  if (soundengine) {
 //       irrklang::vec3df position(23,70,200);

        // start the sound paused:


//        if (_Sound)
//        {

          //irrklang::vec3df velPerSecond(0,0,0);    // only relevant for doppler effects
 //          _Sound ->setVolume( 100);
          //_Sound->setMinDistance(30.0f); // a loud sound
//           _Sound->setIsPaused(true); // unpause the sound
//           return true;
//        }
//        return false;
//    }
    return false;
}
void InitGL::Run() {

    bool quit = false;
    // Diese transformations vectoren enthalten die "steps" für die Animation
    vec3 steptrans;
    vec3 steprotate;
    vec3 stepscale;


    steptrans  = vec3(0.0,-0.5,0.0);
    steprotate = vec3(0.5,0.8,0.0);
    stepscale  = vec3(0.0,0.0,0.0);

    sphere1->Translate(vec3(0.0,-4.0,0.0));

    // timetest
    //Uint32 tickstart = SDL_GetTicks();
    //Uint32 tickend   = tickstart;
    Uint32 elapsed = 0;
    int event = 0;

    //--------------------------------------------------
    // framerate berechene
    //--------------------------------------------------
    int frames = 0;
    Uint32 ms = 0;
    showMenu = true;

    glEnable(GL_DEPTH_TEST);

    //--------------------------------------------------
    // Uncomment, if needed
    //--------------------------------------------------
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //      if (_HasSound)
    //          _Sound = soundengine->play2D("/home/paul/workspace/SpaceEngine/sounds/bell.wav");

    BaseCad2D * cad2 = new BaseCad2D(_ResX,_ResY);
    sPoint p0{100,100};
    sPoint p1{600,800};
    cad2->setPoint0(p0);
    cad2->setPoint1(p1);
    //cad2->setColor(glm::vec4(1.0,1.0,1.0,1.0));

    while ( ! quit) {

        auto start = Clock::now();

       // tickstart =  SDL_GetTicks();
        ms += elapsed;
        frames++;
        if (ms > 1000) {
            _FramerateOut = frames;
            frames = 0;
            ms = 0;
         }

        ShowFramesPerSec(ms);
        ShowCameraPos();

        MousePositions->setText(0,"Mouse X " + IntToString(_Mouse.x) );
        MousePositions->setText(1,"Mouse Y " + IntToString(_Mouse.y) );
        //tickstart = tickend;
        // -------------------------------
        // Test für dynamische winkel
        // abhängig von verbrauchter zeit
        // -------------------------------

       double ups = 5.0f;  // umdrehung per sec...... min

       /*
        * TODO:
        * Klasse für SDL_GetTicks() erstellen ,
        * Funktionen für U/min bzw. U/sec. erstellen
        * verstrichene Zeit ist eben dann max. 60000 für Minute
        * oder 1000 für Secunde !!!
        */
       /* Dieser Bereich für DauerRotation der KAmeara
       double frames = 6000000.0 / second ;

       double mmin = 10.0f;
       double speed  = 0.2f; // geschwindigkeit

       second += elapsed;

       angleX = 360.0f * ups / frames   ;   // upm jetzt
       float ax = static_cast<float> (angleX);

       //checkdegree(ax);
       if (ax > 360.0f )
           ax -= 360;

       if ( second > 60000 )
          second = 0;

       glm::vec3 pos = camera -> GetOrgPos();
       pos = glm::rotateY(pos,ax);

       camera -> SetPos(pos);
       camera -> UpdateCamera();
       */
       uint motionX =0;
       uint motionY =0;

       e.type = 0;
       SDL_PollEvent( &e );
       SDL_PumpEvents();
       event = HandleInput(e,motionX,motionY );
       HandleEvent(e); // Mouseevents

       switch ( event) {
           case KEY_Esc  : quit = true;
               break;

           case KEY_M :{

                showMenu = this->toggleVal(showMenu);
                MainMenu->setActive(showMenu);
               break;
           }

           case KEY_A:{
               camera->MoveLeft(elapsed);
               //cockpit->setPosition(camera);
               //cockpit->Translate(glm::vec3(0.0,0.0,-15.0));


               break;
           }
       case KEY_Left :  {
                camera->YawCameraLeft(elapsed);

                //cockpit->SetDir(camera->GetDir());
                //cockpit->Translate(glm::vec3(0.0,0.0,-15.0));
                //cockpit->Rotate(glm::vec3(camera->PitchCameraDEG(),camera->YawCameraDEG(),camera->RollCameraDEG()));  //
                //cockpit->setPosition(camera);
                break;
            }

       case KEY_Right: {
                camera->YawCameraRight(elapsed);

                //cockpit->SetDir(camera->GetDir());
                //cockpit->Translate(glm::vec3(0.0,0.0,-15.0));
                //cockpit->Rotate(glm::vec3(camera->PitchCameraDEG(),camera->YawCameraDEG(),camera->RollCameraDEG()));   //
                //cockpit->setPosition(camera);
                break;
            }

       case KEY_D: {
               camera->MoveRight(elapsed);
               //cockpit->setPosition(camera);
               //cockpit->Translate(glm::vec3(0.0,0.0,-15.0));

               break;
           }

       case KEY_E: {
                camera->MoveForward(elapsed);
                //cockpit->setPosition(camera);
                //cockpit->Translate(glm::vec3(0.0,0.0,-15.0));

                break;
           }

       case KEY_S: {
            camera->MoveBackward(elapsed);
            //cockpit->setPosition(camera);
            //cockpit->Translate(glm::vec3(0.0,0.0,-15.0));

            break;
            }

       case KEY_Up: {
                camera->PitchCameraUp(elapsed);

                //cockpit->SetDir(camera->GetDir());
                //cockpit->Translate(glm::vec3(0.0,0.0,-15.0));
                //cockpit->Rotate(glm::vec3(camera->PitchCameraDEG(),camera->YawCameraDEG(),camera->RollCameraDEG()));   //
                //cockpit->setPosition(camera);

                break;
            }


       case KEY_Down:
           camera ->PitchCameraDown(elapsed);

           //cockpit->SetDir(camera->GetDir());
           //cockpit->Translate(glm::vec3(0.0,0.0,-15.0));
           //cockpit->Rotate(glm::vec3(camera->PitchCameraDEG(),camera->YawCameraDEG(),camera->RollCameraDEG()));   //
           //cockpit->setPosition(camera);
           break;

        //case KEY_Q: toggleAnimation();
        //   break;

           // Shader select
           case KEY_C   : _CurrentShader = ShaderType::COLOR_SHADER;            _ShaderChanged = true;  break;
           case KEY_T   : _CurrentShader = ShaderType::TEXTURE_SHADER;          _ShaderChanged = true;  break;

           case KEY_F7  : _CurrentShader = ShaderType::GLASS_SHADER;            _ShaderChanged = true;  break;
           case KEY_F8  : _CurrentShader = ShaderType::LIGHT_TEXTURE_SHADER;    _ShaderChanged = true; break;
           case KEY_F9  : _CurrentShader = ShaderType::LIGHT_SHADER;            _ShaderChanged = true;  break;
           case KEY_F10 : _CurrentShader = ShaderType::LIGHT_COLOR_SHADER;      _ShaderChanged = true;  break;
           case KEY_F11 : {
                toogleFullScreen(); break;
           }

           // ORtho oder perspective mode:
           case KEY_O : {

           for (uint i = 0; i < list3D.size(); i++) {
                    list3D[i]->SetProjection(projection->GetOrtho(), true);
                }
                break;
           }
           case KEY_P: {  // Wired

                for (uint i = 0; i < list3D.size(); i++) {
                    list3D[i]->SetProjection(projection->GetPerspective(),false);
                }
               break;
           }

           // Roll Camera left
           case NUM_1: {
               camera->YawEyeLeft(elapsed);
               break;
           }
           // Roll Camera right
           case NUM_3: {
               camera-> YawEyeRight(elapsed);
               break;
           }
           case NUM_2: {
               // Pitch Camera Doun
               camera -> PitchEyeDown(elapsed);
               break;
           }

           case NUM_5: {
               // Pitch camera Up
               camera -> PitchEyeUp(elapsed);//
               break;
           }
           case NUM_PLUS: {
                float s = camera->GetSpeed();
                camera -> SetSpeed(++s);//
                break;
           }
           case NUM_MINUS: {
                float s = camera->GetSpeed();
                s--;
                (s < 0.0f) ? camera -> SetSpeed(0.0f) : camera->SetSpeed(s);//
                break;
           }
       }

       glDepthFunc(GL_LEQUAL);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       if ( ! showPanel) {

           vec3 dummy;
           dummy = vec3(0.0,0.2,0.0);

           if (_UseBlend)
               lightSource->UseBlending(true);
              // glDisable(GL_DEPTH_TEST);
           else
               //glEnable(GL_DEPTH_TEST);
               lightSource->UseBlending(false);

           lightSource->SetColor(glm::vec4(0.5,0.5,0.5,0.3));
           lightSource->SetProjection(projection->GetPerspective());
           lightSource->SetFirstTranslate(true);
           if (_Animate && lightSource->HasAnimation() )
               lightSource ->StepRotate( glm::vec3(0.0,0.2,0.2));

            lightSource->Draw(camera);

            // ===================================
            // Engine Objekte
            // ===================================
            if (_ShaderChanged) {
                if (! list3D.empty() ) {
                    for (unsigned int i=0;i < list3D.size(); i++ )
                        list3D[i]->setActiveShader(_CurrentShader);
                }

                lightSource->setActiveShader(_CurrentShader);
                sphere1-> setActiveShader(_CurrentShader);

                if (cockpit->HasMesh())
                    cockpit->getCockpitMesch()->setActiveShader(_CurrentShader);

            }

             if (! list3D.empty() ) {
                for (unsigned int i=0;i < list3D.size(); i++ ) {
                    dummy = vec3(1.0 * (float) i ,2.0,3.0);
                    list3D[i]->SetProjection(projection->GetPerspective());
                    float hlp = 0.1; //(float) (i+1);
                    glm::vec3 rv(hlp * 0.5);

                    glm::vec3 vt(0.001,0.002,0.003);

                    //list3D[0]->Translate(camera->GetPos() + camera->GetDir());

                    if (_Animate && list3D[i]->HasAnimation()) {
                        list3D[i]->StepTranslate(vt);
                        list3D[i]->StepRotate(rv);
                    }

                    if (_UseBlend)
                        list3D[i]->UseBlending(true);
                    else
                        list3D[i]->UseBlending(false);

                    //list3D[i]->setActiveShader(ShaderType::LIGHT_SHADER);
                    list3D[i]->Draw(camera);
                }

                //if ( PE != nullptr) {
                    //PE->Render(camera,elapsed);
                //}

            }  // Not showpanel

            // ===================================
            // Das beste zum Schluss : Skybox
            // ===================================

            Render(camera->GetView());

            sphere1->setGlasShader(true);
            sphere1->SetColor(glm::vec4(0.0,1.0,0.0,0.5));
            sphere1->SetProjection(projection->GetPerspective());
            sphere1->Rotate(- glm::vec3(camera->PitchCameraDEG(), camera->YawCameraDEG(),camera->RollCameraDEG()));
            sphere1->Translate(camera->GetPos());
            //sphere1->Draw(camera);

            if (cockpit->HasMesh()  && _ShowCockpit) {

                cockpit->getCockpitMesch()->UseBlending(true);
                cockpit->getCockpitMesch()->setGlasShader(true);
                cockpit->setProjectionMatrix(projection->GetPerspective());
                cockpit->Translate(camera->GetPos());
                cockpit->Rotate(camera->MoveDirectionDEG());
            //    cockpit->Draw(camera);
            }
        }

        // ===================================ee
        // Alles für 2D Projektion vorbereiten
        //====================================

        Prepare2D();
        //------------------------------------
        // MainMenu rendern
        // -----------------------------------


        //cad2->setColor(glm::vec4(1.0,0.0,0.0,1.0));
        cad2->Render();

        if ( MainMenu != nullptr  && showMenu) {
            MainMenu ->Render();
        }

        if (! textfields.empty() ) {
            for (uint i = 0; i < textfields.size(); i ++) {
                textfields.at(i)->Render();
            }
        }

        if ( !  objects2D.empty() ) {
            for (uint i =0; i < objects2D.size(); i++) {
                (objects2D[i])->Render();
            }
        }

        if ( ! buttons.empty() ) {
            for ( uint i = 0; i < buttons.size(); i++) {
                buttons[i]->Render();

            }
        }

        Restore3D();

        SDL_GL_SwapWindow(window);

        auto end = Clock::now();
        auto el = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000;
        elapsed =   static_cast<uint32>(el);//500;
     }
}

void InitGL::Done() {
}

void InitGL::Prepare2D() {
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
}

void InitGL::Restore3D() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glDepthMask(1);
}



uint InitGL::HandleEvent(SDL_Event e) {
    switch (e.type) {
        case      SDL_MOUSEMOTION :

            _Mouse.x = e.motion.x;
            _Mouse.y = e.motion.y;

            _MouseButtons = SDL_GetMouseState(&e.motion.x, &e.motion.y);
            OnMouseMove(e.motion.x, e.motion.y, _MouseButtons);
            break;

        case SDL_MOUSEBUTTONDOWN: {

            if ( e.button.button == SDL_BUTTON_LEFT ) {
                OnLeftMouseButtonDown(e.motion.x, e.motion.y);
            }
            break;
         }

        case SDL_MOUSEBUTTONUP: {

        if ( e.button.button == SDL_BUTTON_LEFT ) {
                OnLeftMouseButtonUp(e.motion.x, e.motion.y);
            }
            break;
        }
    }
    return  e.type; // Falls wo gebraucht wird
}

//-------------------------------------------------
// Mouse events
//-------------------------------------------------

MOUSE InitGL::convertMouse(int x, int y) {

    MOUSE m;
//    float fx = (float)x * MouseResX;
//  float fy = (float)y * MouseResY;

//    m.x = (int) fx;
//    m.y = (int) fy;
    m.x =  x;
    m.y =  y;

    return  m;
}
void InitGL::OnMouseMove(int &x, int &y, uint32 buttonstate) {

    MOUSE m = convertMouse(x,y);

    for (uint i = 0; i < textfields.size(); i++) {

        if (textfields.at(0)->IsDragging() && (buttonstate & SDL_BUTTON_LMASK) != 0) {
            textfields.at(0)->OnDrag(m.x, m.y);
        }
    }
}

void InitGL::OnLeftMouseButtonDown(int &x, int &y) {

    MOUSE m = convertMouse(x,y);

    for (uint i = 0; i < textfields.size(); i++) {
        if (textfields.at(i)->intersect(m.x,m.y))
            textfields.at(i)->OnStartDrag(m.x, m.y);
    }

    if ( ! buttons.empty()  ) {
        for (uint i = 0; i < buttons.size(); i++) {
            if (buttons[i]->intersect(m.x, m.y) )
                buttons[i]->OnClick();
        }
    }

    if ( ! MainMenu->containerList.empty() && MainMenu != nullptr && MainMenu->Active()) {

        for ( uint i = 0; i< MainMenu->containerList.size(); i++) {
            if ( ! MainMenu->containerList.at(i)->buttons.empty()) {

                for (uint j=0; j< MainMenu->containerList.at(i)->buttons.size(); j ++) {
                    if (MainMenu->containerList.at(i)->buttons.at(j)->intersect(m.x, m.y) ) {
                        MainMenu->containerList.at(i)->buttons.at(j)->OnClick();

                    }
                }
             if ( ! MainMenu->containerList.at(i)->controlls2D.empty() ) {
                for (uint j=0; j< MainMenu->containerList.at(i)->controlls2D.size(); j ++) {
                    if (MainMenu->containerList.at(i)->controlls2D.at(j)->intersect(m.x, m.y) ) {
                        MainMenu->containerList.at(i)->controlls2D.at(j)->OnClick();
                    }
                }
             }
          }
       }
    }
}

void InitGL::OnLeftMouseButtonUp(int &x, int &y) {

    MOUSE m = convertMouse(x,y);
    if ( ! MainMenu->containerList.empty() && MainMenu != nullptr && MainMenu->Active()) {

        for ( uint i = 0; i< MainMenu->containerList.size(); i++) {
            if ( ! MainMenu->containerList.at(i)->buttons.empty()) {

                for (uint j=0; j< MainMenu->containerList.at(i)->buttons.size(); j ++) {
                    if (MainMenu->containerList.at(i)->buttons.at(j)->intersect(m.x, m.y) ) {
                        MainMenu->containerList.at(i)->buttons.at(j)->OnRelease();
                    }
                }
            }

            if ( ! MainMenu->containerList.at(i)->controlls2D.empty() ) {
            //    for (uint j=0; j< MainMenu->containerList.at(i)->controlls2D.size(); j ++) {
            //        if (MainMenu->containerList.at(i)->controlls2D.at(j)->intersect(m.x, m.y) ) {
            //            MainMenu->containerList.at(i)->controlls2D.at(j)->OnClick();
            //        }
            //    }
            }
        }
    }

    if ( ! buttons.empty()  ) {
        for (uint i = 0; i < buttons.size(); i++) {
            if (buttons[i]->intersect(m.x, m.y) )
                buttons[i]->OnRelease();
        }
    }

    for (uint i = 0; i < textfields.size(); i++) {
        if (textfields.at(i)->IsDragging() ) {
            textfields.at(i)->OnEndDrag(m.x, m.y);
        }
    }
}


int InitGL::HandleInput(SDL_Event e, uint &mox, uint &moy) {

    switch (e.type) {
   //
        case SDL_MOUSEWHEEL :   return  MOUSE_Wheel;

        // Keyboard
        case SDL_KEYDOWN : {
            switch(e.key.keysym.sym ) {
                case SDLK_RIGHT     : return KEY_Right;     break;
                case SDLK_LEFT      : return KEY_Left;      break;
                case SDLK_UP        : return KEY_Up;        break;
                case SDLK_DOWN      : return KEY_Down;      break;
                case SDLK_ESCAPE    : return KEY_Esc;       break;
                // Ziffernblock:
                case SDLK_KP_0      : return NUM_0;         break;
                case SDLK_KP_1      : return NUM_1;         break;
                case SDLK_KP_2      : return NUM_2;         break;
                case SDLK_KP_3      : return NUM_3;         break;
                case SDLK_KP_4      : return NUM_4;         break;
                case SDLK_KP_5      : return NUM_5;         break;
                case SDLK_KP_6      : return NUM_6;         break;
                case SDLK_KP_7      : return NUM_7;         break;
                case SDLK_KP_8      : return NUM_8;         break;
                case SDLK_KP_9      : return NUM_9;         break;
                case SDLK_KP_PLUS   : return NUM_PLUS;      break;
                case SDLK_KP_MINUS  : return NUM_MINUS;     break;

                case SDLK_a         : return KEY_A;         break;
                case SDLK_s         : return KEY_S;         break;
                case SDLK_d         : return KEY_D;         break;
                case SDLK_e         : return KEY_E;         break;
                case SDLK_p         : return KEY_P;         break;// PerspectiveMode
                case SDLK_o         : return KEY_O;         break;// Orthomode
                case SDLK_c         : return KEY_C;         break;// Colored Draw
                case SDLK_t         : return KEY_T;         break;// Textured Draw
                case SDLK_q         : return KEY_Q;         break;
                case SDLK_m         : return KEY_M;         break;

                case SDLK_F1        : return KEY_F1;        break;
                case SDLK_F2        : return KEY_F2;        break;
                case SDLK_F3        : return KEY_F3;        break;
                case SDLK_F4        : return KEY_F4;        break;
                case SDLK_F5        : return KEY_F5;        break;
                case SDLK_F6        : return KEY_F6;        break;
                case SDLK_F7        : return KEY_F7;        break;
                case SDLK_F8        : return KEY_F8;        break;
                case SDLK_F9        : return KEY_F9;        break;
                case SDLK_F10       : return KEY_F10;       break;
                case SDLK_F11       : return KEY_F11;       break;
                case SDLK_F12       : return KEY_F12;       break;

                default : return NO_INPUT;break;
            }
       }
        // Mouse Buttons
        case SDL_MOUSEBUTTONUP : {
            switch (e.button.button) {
                case SDL_BUTTON_LEFT    :   return MOUSE_BTN_Left_UP;      break;
                case SDL_BUTTON_MIDDLE  :   return MOUSE_BTN_MiddLe_UP;    break;
                case SDL_BUTTON_RIGHT   :   return MOUSE_BTN_Right_UP;     break;
            }
        }

        case SDL_MOUSEBUTTONDOWN : {
            switch (e.button.button) {
                case SDL_BUTTON_LEFT    :   return MOUSE_BTN_Left_DOWN;      break;
                case SDL_BUTTON_MIDDLE  :   return MOUSE_BTN_MiddLe_DOWN;    break;
                case SDL_BUTTON_RIGHT   :   return MOUSE_BTN_Right_DOWN;     break;
            }
        }

        case SDL_MOUSEMOTION: {

            mox = e.motion.x;
            moy = e.motion.y;
         //   _Mouse.lastx = e.motion.x;
         //   _Mouse.lasty = e.motion.y;
            return MOUSE_Move;
        }
        default : return NO_INPUT;
    }

    return NO_INPUT;
}

void InitGL::sdl_die( std::string msg)
{
    fprintf(stderr,"%s: %s \n", msg.c_str(),SDL_GetError());

}



