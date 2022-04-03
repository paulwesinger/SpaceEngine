#include "engine.h"
#include "../utils/utils.h"
#include "../landscape/landscape.h"
//#include "../defaults.h"

// macro
#define safeDelete(pt) \
    if (pt != nullptr) \
        delete pt;

//------------------------------------------------------------------
// static functions for Button Handler
//------------------------------------------------------------------
void EnableButton1() {
    if ( butn0 != nullptr)
        butn0->enable();
    if ( butn1 != nullptr)
        butn1->enable();
}
void DisableButton1() {
    if ( butn0 != nullptr)
        butn0->disable();
    if ( butn2 != nullptr)
        butn2->disable();
}
void Button3() {
    if ( butn1 != nullptr)
        butn1->disable();
}

void FxFog() {
    loginfo("TestFunc2","Fog");
}

void EngineTestFunc2() {
     loginfo("TestFunc2","Engine:: EngineTestFunc 2");
}
void EngineTestFunc3() {
    loginfo("TestFunc3","Engine:: EngineTestFunc 3");
}

void EngineTestFunc4() {
    loginfo("TestFunc4","Engine:: EngineTestFunc 4");
}

//---------------------------------
// DrawPanel
//---------------------------------
void CEngine::DrawPanel() {
    InitGL::togglePanel2D();
}

CEngine::CEngine(std::string titel) :
        InitGL(titel){
    con1                = nullptr;
    con2                = nullptr;

    txtFrameperSec      = nullptr;
    checkBoxAnimation   = nullptr;
    toogleSkyBoxBtn     = nullptr;

    cameraX             = nullptr;
    cameraY             = nullptr;
    cameraZ             = nullptr;
}

CEngine::~CEngine(){
    safeDelete (con1)
    safeDelete (con2)

    //safeDelete(fogBtn);
}

void CEngine::Done() {
    InitGL::Done();
}

void CEngine::Run() {

    initMenu();
    Init2D();
    Init3D();
    InitButtons();

    InitGL::Run();
}

// ---------------------------------------------------------------
// Place here Functons for button handler..
// ---------------------------------------------------------------

void CEngine::functoogleAnimation(bool checked) {

    InitGL::toggleAnimation();  // eigntlich startanimation..

}

void CEngine::functoogleBlend(bool checked) {

       InitGL::toggleBlend();
}

void CEngine::funcToogleSkybox() {

    renderSkybox = InitGL::toggleVal(renderSkybox);
}

void CEngine::funcFog(){
    loginfo("Fog - function");
}

void CEngine::Render(glm::mat4 cam) {

    if (renderSkybox)
        InitGL::Render(cam);
}

// --------------------------------------------------------------
// Init Methods for Engines
// --------------------------------------------------------------
void CEngine::initMenu(){

    //                  |Resolution|  | Position           | width,height, colors             |
     MainMenu = new CMenu(_ResX, _ResY, 0, 0, MENU_WIDTH, MENU_HEIGHT, glm::vec4(0.1,0.1,0.1,0.8), glm::vec4(0.9,0.9,0.9,1.0));
    // loginfo("Erstelle Main Menu ...... done","InitGL::InitEngineObject");

    int curr_y;
    // -------------------------------------
    // Standard Menu ist in Initgl vorhanden
    // jetzt  befüllen
    //--------------------------------------

    con1 = new CControllContainer(MainMenu->Pos().x,
                                  MainMenu->Pos().y,
                                  MainMenu->Width(), 0);

    butn0 = new CTextButton(_ResX, _ResY,"../SpaceEngine/images/ButtonReleased.png", "2D-Panel", con1->NextControllPos() );
    butn0->setSize(BTN_WIDTH,BTN_HEIGHT);
    butn0->setScale(TEXT::SCALE_SMALL);
    butn0->setColor(BTN_ENABLE);
    butn0->setDisablecolor(BTN_DISABLE);
    butn0->AddHandler(CEngine::DrawPanel);
    con1->addButton(butn0);

    butn1 = new CImageButton(_ResX, _ResY,"../SpaceEngine/images/ButtonReleased.png", "../SpaceEngine/images/ShowSkyBox.png", con1->NextControllPos());
    butn1->useShader(TEXTURE_SHADER);
    butn1->setColor(BTN_ENABLE);
    butn1->setDisablecolor(BTN_DISABLE);
    butn1->setSize(BTN_WIDTH,BTN_HEIGHT);
    butn1->AddHandler(DisableButton1);
    con1->addButton(butn1);

    butn2 = new CImageButton(_ResX, _ResY,"../SpaceEngine/images/ButtonReleased.png",  "../SpaceEngine/images/NewCube.png", con1->NextControllPos());
    butn2->setSize(BTN_WIDTH,BTN_HEIGHT);
    butn2->setScale(TEXT::SCALE_SMALL);
    butn2->setColor(BTN_ENABLE);
    butn2->setDisablecolor(BTN_DISABLE);
    butn2->AddHandler(Button3);
    con1->addButton(butn2);
    MainMenu->addConatiner(con1);

    curr_y = MainMenu->CurrentY() + MENU_SPACER;

    //---------------------------------------------------
    // 2. container
    //---------------------------------------------------
    con2 = new CControllContainer(MainMenu->Pos().x,
                                             curr_y,
                                  MainMenu->Width(),0);
    con2->addSpacer();
    toogleSkyBoxBtn = new CImageButton(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", "../SpaceEngine/images/ToogleSkybox.png",con2->NextControllPos() );
    toogleSkyBoxBtn->setColor(BTN_ENABLE);
    toogleSkyBoxBtn->setDisablecolor(BTN_DISABLE);
    toogleSkyBoxBtn->setSize(BTN_WIDTH,BTN_HEIGHT);
    toogleSkyBoxBtn->AddHandler(CEngine::funcToogleSkybox);
    con2->addButton(toogleSkyBoxBtn);

    con2->addSpacer();
    //-----------------------------------------------------
    // Textedit:
    //-----------------------------------------------------
    sSize s;
    sPoint p;
    //con2->addSpacer();
    s.w = MainMenu->Width() - CONTROLL::MARGIN_X ;
    s.h = CONTROLL::HEIGHT;

    p = con2->NextControllPos();
    txtFrameperSec = new TextEdit(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0));
    txtFrameperSec->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(txtFrameperSec);
    // add label for Frames to buildin textrender label
    txtFrameperSec->setLabel("FPS");

    //----------------------------------------------------
    // checkbox für Animation
    //----------------------------------------------------
    p = con2->NextControllPos();

    checkBoxAnimation = new CheckBox(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) );
    checkBoxAnimation->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    checkBoxAnimation->AddHandler(CEngine::functoogleAnimation);
    checkBoxAnimation->setChecked();
    con2->addControll2D(checkBoxAnimation);
    // add label for Frames to buildin textrender label
    checkBoxAnimation->setLabel("Animate");

    //----------------------------------------------------
    // checkbox für Blending
    //----------------------------------------------------
    p = con2->NextControllPos();

    checkBoxBlending = new CheckBox(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) );
    checkBoxBlending->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    checkBoxBlending->AddHandler(CEngine::functoogleBlend);
    checkBoxBlending->setChecked();
    con2->addControll2D(checkBoxBlending);
    // add label for Frames to buildin textrender label
    checkBoxBlending->setLabel("Blending");
    // ---------------------------------------------------
    // Statusfenster(pos) von Camera:
    //----------------------------------------------------
    p = con2->NextControllPos();
    cameraX = new TextEdit(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0));
    cameraX->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameraX);
    // add label for Frames to buildin textrender label
    cameraX->setLabel("Cam X");

    p = con2->NextControllPos();
    cameraY = new TextEdit(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0));
    cameraY->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameraY);
    // add label for Frames to buildin textrender label
    cameraY->setLabel("Cam Y");

    p = con2->NextControllPos();
    cameraZ = new TextEdit(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0));
    cameraZ->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameraZ);
    // add label for Frames to buildin textrender label
    cameraZ->setLabel("Cam Z");

    p = con2->NextControllPos();
    camerayaw = new TextEdit(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0));
    camerayaw->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(camerayaw);
    // add label for Frames to buildin textrender label
    camerayaw->setLabel("Cam Yaw");

    p = con2->NextControllPos();
    cameradirZ = new TextEdit(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0));
    cameradirZ->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameradirZ);
    // add label for Frames to buildin textrender label
    cameradirZ->setLabel("CamDir.Z");

    p = con2->NextControllPos();
    cameradirX = new TextEdit(_ResX, _ResY, "../SpaceEngine/images/ButtonReleased.png", p,s ,glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0));
    cameradirX->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameradirX);
    // add label for Frames to buildin textrender label
    cameradirX->setLabel("CamDir.X");

    MainMenu->addConatiner(con2);
}

void CEngine::ShowFramesPerSec(uint32 sec) {

    static uint32 ms = 0;

    ms += sec;
    if (ms > 1000) {
        if (txtFrameperSec != nullptr) {

            ms = 0;
            TextRender * t = txtFrameperSec->getTextPtr();

            if (t != nullptr) {
                t->setText(0,IntToString(_FramerateOut));
                t->Render();
            }
        }
    }
}

void CEngine::ShowCameraPos() {
    if (cameraX != nullptr) {
        TextRender * tX = cameraX->getTextPtr();
        if (tX != nullptr) {
            tX->setText(0, FloatToString(camera->GetPos().x));
            tX->Render();
        }
    }

    if (cameraY != nullptr ) {
        TextRender * tY = cameraY->getTextPtr();
        if (tY != nullptr) {
            tY->setText(0, FloatToString(camera->GetPos().y));
            tY->Render();
        }
    }

    if (cameraZ != nullptr) {
        TextRender * tZ = cameraZ->getTextPtr();
        if (tZ != nullptr) {
            tZ->setText(0, FloatToString(camera->GetPos().z));
            tZ->Render();
        }
    }

    if (camerayaw != nullptr) {
        TextRender * tyaw = camerayaw->getTextPtr();
        if (tyaw != nullptr) {
            tyaw->setText(0, FloatToString(camera->YawCameraDEG()));
            tyaw->Render();
        }
    }

    if (cameradirZ != nullptr) {
        TextRender * tdir = cameradirZ->getTextPtr();
        if (tdir != nullptr) {
            tdir->setText(0, FloatToString(camera->GetDir().z));
            tdir->Render();
        }
    }

    if (cameradirX != nullptr) {
        TextRender * tdir = cameradirX->getTextPtr();
        if (tdir != nullptr) {
            tdir->setText(0, FloatToString(camera->GetDir().x));
            tdir->Render();
        }
    }
}

void CEngine::Init2D() {

    //================================
    // Init 2D Objects
    // ==========y=====================

    // Testweise mal einfügen
    loginfo("============================");
    loginfo("Erstelle 2D Objekte.........");
    loginfo("============================");
    logimage("Erstelle TestIcon..........");
    base2d = new Base2D(_ResX, _ResY,"../SpaceEngine/icons/ibus-setup-hangul.png");
    base2d->setPos(500,400);
    add2Dobject(base2d);
  }

void CEngine::Init3D(){

   logEmptyLine();
   loginfo("============================");
   loginfo("Erstelle 3D Objekte.........");
   loginfo("============================");

   fileUtil * fileutil = new fileUtil();
   bool ok;
   //--------------------------------------
   // loading Textured cubes
   //--------------------------------------
   ok = fileutil->readLine(OBJECT3D_CFG + "TexturedCubes/TexCubes.cfg", object3DTexturedList);
   if (ok) {
        if ( ! loadTexturedCubes() )
            logwarn("Fehler: Keine Textured Cubes gefunden oder Fehler im Pfad!");
   }
   else
       logwarn("Fehler: Datei  < config/TexCubes.cfg  > nicht gefunden !");


   // --------------------------------------
   // colored cubes loading
   //---------------------------------------
   ok = fileutil->readLine(OBJECT3D_CFG + "ColoredCubes/ColorCubes.cfg", object3DColoredList);
   if (ok) {
        if ( ! loadColorCubes() )
            logwarn("Fehler: Keine Colored Cubes gefunden oder Fehler im Pfad!");
   }
   else
       logwarn("Fehler: Datei  < config/ColorCubes.cfg  > nicht gefunden !");


   // --------------------------------------
   // Landscape loading
   //---------------------------------------
   ok = fileutil->readLine(OBJECT3D_CFG + "Landscapes/Landscapes.cfg", object3DLandscapeList);
   if (ok) {
        if ( ! loadLandscape() )
            logwarn("Fehler: Keine Landscape gefunden oder Fehler im Pfad!");
   }
   else
       logwarn("Fehler: Datei  < config/Landscape.cfg  > nicht gefunden !");

   // --------------------------------------
   // Cockpit loading
   //---------------------------------------
   ok = fileutil->readLine(COCKPIT_CFG + "Cockpit.cfg", objectCockpitList);
   if (ok) {
        if ( ! loadCockpits() )
            logwarn("Fehler: Keine Cockpits gefunden oder Fehler im Verzeichnißpfad!");
   }
   else
       logwarn("Fehler: Datei  < config/Landscape.cfg  > nicht gefunden !");


   logEmptyLine() ;
   loginfo("----------------------------");
   loginfo(" Init 3D Objects ");
   loginfo("     READY");
   loginfo("----------------------------");
}


bool CEngine::loadLandscape() {
    loginfo("Lade Datei |Landscapes.cfg|","CEngine::loadLandscapes");

     // Liste mit Objekten abarbeiten :

    if (object3DLandscapeList.empty() )
        return false;

    logwarn("Anzahl der Landscapes: " + IntToString(object3DLandscapeList.size()));

    for (unsigned int i = 0; i < object3DLandscapeList.size(); i++) {

         std::string path = OBJECT3D_CFG + "Landscapes/" + object3DLandscapeList[i];

         loginfo("Erstelle Object: .......< " + path+ " >","Engine::loadLandscapes");

         fileUtil * objreader = new fileUtil;
         std::vector<std::string> objconfig;
         objreader->readLine(path, objconfig);

         if( ! objconfig.empty() ) {

             loginfo("objconfig size : " + IntToString(objconfig.size()),"Engine::loadLandScape");

             sLandscape landscape;
             if (initLandscape(landscape,objconfig)) {

                 LandScape * obj = new LandScape();
                 //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 if ( landscape.textures == "NONE" )
                     obj->SetHasTextures( false);
                 else
                     obj->SetHasTextures( true);

                 obj->SetColor(glm::vec4(landscape.color.x, landscape.color.y, landscape.color.z, landscape.color.w));
                 obj->Rotate(glm::vec3(landscape.trans.rotate.x, landscape.trans.rotate.y, landscape.trans.rotate.z) );
                 obj->Translate(glm::vec3(landscape.trans.translate.x, landscape.trans.translate.y, landscape.trans.translate.z));
                 obj->Scale(glm::vec3(landscape.trans.scale.x, landscape.trans.scale.y, landscape.trans.scale.z));

                 obj->setPatchX(landscape.patchX);
                 obj->setPatchZ(landscape.patchZ);
                 obj->setRasterX(landscape.rasterX);
                 obj->setRasterZ(landscape.rasterZ);

                 //----------------------------------------
                 // Add textures , if we have some
                 // ---------------------------------------
                 bool texturesok;
                 std::vector<std::string> images;

                 std::string path = landscape.textures;
                 if ( landscape.textures != "NONE" ) {
                     fileUtil fu;

                     texturesok =  fu.readLine(path, images);

                     if (texturesok)
                         obj->addTexture(images,"Engine::loadLandscape");
                     else
                         logwarn("Engine::loadScape :  konnte Textures nicht laden ! ","Engine::loadLandscape");
                 }

                 if (obj->init() ) {
                     loginfo("Landscape initialisisert ","CEngine::loadLandscape");
                     add2List(obj,LIGHT_SHADER); //)TEXTURE_SHADER
                 }
                 else
                    logwarn("Landscape wurde nicht initialisisert ","CEngine::loadLandscape");
             }
             else
                 logwarn("konnte Structure Landscape nicht initialisieren !!", "CEngine::loadLandscpae" );
                // Hier die neuen stringpart functions einbauen

             loginfo("Prepare for next Object: ","CEngine::init3D");
             logEmptyLine();
        }
    }
    return true;
}

bool CEngine::loadTexturedCubes(){

    loginfo("Lade Datei |TexCubes.cfg|","CEngine::loadTextureCubes");

     // Liste mit Objekten abarbeiten :

    if (object3DTexturedList.empty() )
        return false;

    for (unsigned int i = 0; i < object3DTexturedList.size(); i++) {

         std::string path = OBJECT3D_CFG + "TexturedCubes/" + object3DTexturedList[i];

         loginfo("Erstelle Textured Cubes: .......< " + path+ " >","Engine::loadTexturedCubes");

         fileUtil * objreader = new fileUtil;
         std::vector<std::string> objconfig;
         objreader->readLine(path, objconfig);


         if( ! objconfig.empty() ) {

             s3DStruct s3D;

             if (init3DStruct(s3D,objconfig)) {

                 CCube * obj = new CCube();
                 //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 if ( s3D.textures == "" )
                     obj->SetHasTextures( false);
                 else
                     obj->SetHasTextures( true);

                 obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 obj->SetFirstTranslate( ( s3D.firstTranslate == 1) ? true: false);
                 obj->Rotate(glm::vec3(s3D.trans.rotate.x, s3D.trans.rotate.y, s3D.trans.rotate.z) );
                 obj->Translate(glm::vec3(s3D.trans.translate.x, s3D.trans.translate.y, s3D.trans.translate.z));
                 obj->Scale(glm::vec3(s3D.trans.scale.x, s3D.trans.scale.y, s3D.trans.scale.z));
                 obj->SetHasAlpha(true);
                 obj->SetFrontFace(GL_CCW);

                 //----------------------------------------
                 // Add textures , if we have some
                 // ---------------------------------------
                 bool texturesok;
                 std::vector<std::string> images;

                 std::string path = s3D.textures;
                 if ( s3D.textures != "none" ) {
                     fileUtil fu;

                     texturesok =  fu.readLine(path, images);
                     if (texturesok)
                         obj->addTexture(images,"InitGL::add3DObject");
                     else
                         logwarn("Engine::loadTexturedCube: Konnte Textures nicht laden ! ","CEngine::loadTexturedCube");
                 }
                 else {

                     int count = 0;

                     if (s3D.texture0 != "" ) {
                         images.push_back(s3D.texture0);
                         count ++;
                     }

                     if (s3D.texture1 != "" ) {
                         images.push_back(s3D.texture1);
                         count ++;
                     }

                     if (s3D.texture2 != "" ) {
                         images.push_back(s3D.texture2);
                         count ++;
                     }

                     if (s3D.texture3 != "" ) {
                         images.push_back(s3D.texture3);
                         count ++;
                     }

                     if (s3D.texture4 != "" ) {
                         images.push_back(s3D.texture4);
                         count ++;
                     }

                     obj->addTexture(images,"InitGL::add3DObject");
                     loginfo("added " + IntToString(count) + " Textures ", "Engine::loadTexturedCubes");

                 }

                 loginfo("s3D initialisisert ","CEngine::init3D");
                 add2List(obj,LIGHT_SHADER); //LIGHT_SHADER)

             }
             else
                 logwarn("konnte s3D nicht initialisieren !!", "CEngine::init3D" );
                // Hier die neuen stringpart functions einbauen

             loginfo("Prepare for next Object: ","CEngine::init3D");
             logEmptyLine();
        }
    }
    return true;
}

bool CEngine::loadCockpits() {
    loginfo("Lade Datei |Cockpits.cfg | ","CEngine::loadCockpits");

     // Liste mit Cockpits abarbeiten :

    if (objectCockpitList.empty() )
        return false;

    for (unsigned int i = 0; i < objectCockpitList.size(); i++) {

         std::string path = COCKPIT_CFG + objectCockpitList[i];

         loginfo("Erstelle Object: .......< " + path+ " >","Engine::loadCockpits");

         fileUtil * objreader = new fileUtil;
         std::vector<std::string> objconfig;
         objreader->readLine(path, objconfig);


         if( ! objconfig.empty() ) {

             s3DStruct s3D;

             if (init3DStruct(s3D,objconfig)) {

                 CCube * obj = new CCube();
                 //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 if ( s3D.textures == "" )
                     obj->SetHasTextures( false);
                 else
                     obj->SetHasTextures( true);

                 obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 obj->SetFirstTranslate( ( s3D.firstTranslate == 1) ? true: false);
                 obj->Rotate(glm::vec3(s3D.trans.rotate.x, s3D.trans.rotate.y, s3D.trans.rotate.z) );
                 obj->Translate(glm::vec3(s3D.trans.translate.x, s3D.trans.translate.y, s3D.trans.translate.z));
                 obj->Scale(glm::vec3(s3D.trans.scale.x, s3D.trans.scale.y, s3D.trans.scale.z));
                 obj->SetHasAlpha(true);
                 obj->SetFrontFace(GL_CW);

                 //----------------------------------------
                 // Add textures , if we have some
                 // ---------------------------------------
                 bool texturesok;
                 std::vector<std::string> images;

                 std::string path = s3D.textures;
                 if ( s3D.textures != "" ) {
                     fileUtil fu;

                     texturesok =  fu.readLine(path, images);
                     if (texturesok)
                         obj->addTexture(images,"InitGL::addCockpitTexture");
                     else
                         logwarn("Engine::loadCockpits: Konnte Textures nicht laden ! ","CEngine::loadCockpits");
                 }
                 loginfo("Cockpit initialisisert ","CEngine::loadCockpit");

                 obj->initShader(COLOR_SHADER,cubeshaderprog_color);
                 obj->initShader(TEXTURE_SHADER,cubeshaderprog_tex);
                 obj->initShader(LIGHT_SHADER, cubeshaderprog_normals);
                 obj->initShader(LIGHT_COLOR_SHADER, cubeshaderprog_color_normal);
                 obj->initShader(GLASS_SHADER,glasshader);
                 obj->setActiveShader(TEXTURE_SHADER);
                 obj->SetFrontFace(GL_CW);

                 cockpit->setMesh(obj);
                 //add2List(obj,LIGHT_SHADER); //LIGHT_SHADER)

             }
             else
                 logwarn("konnte Cockpit nicht initialisieren !!", "CEngine::loadCockpits" );
                // Hier die neuen stringpart functions einbauen

             loginfo("Prepare for next cockpit: ","CEngine::loadcockpit");
             logEmptyLine();
        }
    }
    return true;
}

bool CEngine::loadColorCubes() {

    loginfo("Lade Datei |ColorCubes.cfg|","CEngine::loadColorCubes");

     // Liste mit Objekten abarbeiten :

    if (object3DColoredList.empty() )
        return false;

    for (unsigned int i = 0; i < object3DColoredList.size(); i++) {

         std::string path = OBJECT3D_CFG + "ColoredCubes/" + object3DColoredList[i];

         loginfo("Erstelle Colored Cubes: .......< " + path+ " >","Engine::LoadColoredCubes");

         fileUtil * objreader = new fileUtil;
         std::vector<std::string> objconfig;
         objreader->readLine(path, objconfig);


         if( ! objconfig.empty() ) {

             s3DStruct s3D;

             if (init3DStruct(s3D,objconfig)) {

                 CColorCube * obj = new CColorCube();
                 //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 obj->SetHasTextures( false);
                 obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 obj->SetFirstTranslate( ( s3D.firstTranslate == 1) ? true: false);
                 obj->Rotate(glm::vec3(s3D.trans.rotate.x, s3D.trans.rotate.y, s3D.trans.rotate.z) );
                 obj->Translate(glm::vec3(s3D.trans.translate.x, s3D.trans.translate.y, s3D.trans.translate.z));
                 obj->Scale(glm::vec3(s3D.trans.scale.x, s3D.trans.scale.y, s3D.trans.scale.z));
                 obj->SetFrontFace(GL_CCW);

                 loginfo("s3D initialisisert ","CEngine::init3D");

                 add2List(obj,LIGHT_COLOR_SHADER);
             }
             else
                 logwarn("konnte s3D nicht initialisieren !!", "CEngine::init3D" );
                // Hier die neuen stringpart functions einbauen

             loginfo("Prepare for next Object: ","CEngine::init3D");
             logEmptyLine();
        }
    }
    return true;
}


void CEngine::InitButtons() {

    logEmptyLine();
    loginfo("============================");
    loginfo("Erstelle Buttons ...........");
    loginfo("============================");

    loadButtons();
}

void CEngine::loadButtons() {
    // Open file
    bool ok;
    fu = new fileUtil();

    ok = fu->readLine(BUTTONS_CFG + "ButtonList.cfg", btnList);

    if (ok) {
        loginfo("Lade Datei |ButtonList.cfg|","CEngine::loadbuttons");
        logEmptyLine();

        for (unsigned int i = 0; i < btnList.size(); i++  ){

            std::string path = BUTTONS_CFG + btnList[i];

            fileUtil * btnreader = new fileUtil;
            std::vector<std::string> btnconfig;
            btnreader->readLine(path, btnconfig);



            if ( ! btnconfig.empty() ) {

                loginfo("Erstelle Button: .......< " + path+ " >", "Engine::loadButtons");

                sButtonStruct btnStruct;
                if  (initButtonStruct(btnStruct,btnconfig) ) {
                    sPoint pos;
                    CButton * btn = new CTextButton(_ResX,_ResY ,btnStruct.path,"",pos);//   btnStruct.path);
                    btn->setPos(btnStruct.PosX,btnStruct.PosY);
                    btn->setSize(btnStruct.SizeX, btnStruct.SizeY);
                    btn->setbuttonColors(glm::vec3(btnStruct.ImageRed,btnStruct.ImageGreen,btnStruct.ImageBlue),
                                         glm::vec3(btnStruct.TextRed,btnStruct.TextGreen,btnStruct.TextBlue));

                    switch (i) {
                        case 0: btn ->AddHandler(funcToogleSkybox); break;
                        case 1: btn ->AddHandler(EngineTestFunc2); break;
                        case 2: btn ->AddHandler(EngineTestFunc3); break;
                    default:
                        btn ->AddHandler(EngineTestFunc4);
                    }
                    if (btnStruct.Enable > 0 )
                        btn->enable();
                    else
                        btn->disable();
                    btn->setText("Edit");
                    addButton(btn);

                    loginfo(".........Done", "Engine::loadButtons");
                    logEmptyLine();
                }
            }
        }
    }
    else
        logwarn("Fehler: Datei | config/ButtonList nicht gefunden ! |");

    logEmptyLine() ;
    loginfo("----------------------------");
    loginfo(" Load Button Objects ");
    loginfo("        READY");
    loginfo("----------------------------");

}

std::string &CEngine::getValueItem(std::string &s, std::string erasestring) {
    return s.erase(0,erasestring.length() ) ;
}

bool CEngine::initLandscape(sLandscape &ls, std::vector<std::string> &cfg){
    if (cfg.size() >= CFG_3D_SIZE ) {

        //+---------------------------------------------------------------------+
        //+     VORGEHEN :                                                      |
        //+     Liste abarbeiten, Teilstring bis " " ermitteln,                 |
        //+     Variablen name = Teilstring --> 2. Teilstring in Wert wandeln   |
        //+     und in der s3DStruct zuweisen                                   |
        //+---------------------------------------------------------------------+

        for (uint i = 0; i < cfg.size(); i++) {
            std::vector<std::string> parts = split(cfg.at(i), SPACE);

            if (parts.at(0) == "colorRed")
                ls.color.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorGreen")
                ls.color.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorBlue")
                ls.color.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorAlpha")
                ls.color.w = StringToFloat(parts.at(1));

            if (parts.at(0) == "hasLight")
                ls.hasLight = StringToInt(parts.at(1));

            if (parts.at(0) == "textures")
                ls.textures = parts.at(1);

            if (parts.at(0) == "translateX")
                ls.trans.translate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateY")
                ls.trans.translate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateZ")
                ls.trans.translate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateX")
                ls.trans.rotate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateY")
                ls.trans.rotate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateZ")
                ls.trans.rotate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleX")
                ls.trans.scale.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleY")
                ls.trans.scale.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleZ")
                ls.trans.scale.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "patchX")
                ls.patchX = StringToInt(parts.at(1));

            if (parts.at(0) == "patchZ")
                ls.patchZ = StringToInt(parts.at(1));

            if (parts.at(0) == "rasterX")
                ls.rasterX = StringToFloat(parts.at(1));

            if (parts.at(0) == "rasterZ")
                ls.rasterZ = StringToFloat(parts.at(1));


        }
        return true;

    }
    return false;
}

bool CEngine::init3DStruct(s3DStruct &d3s, std::vector<std::string> &cfg){
    if (cfg.size() >= CFG_3D_SIZE ) {

        //+---------------------------------------------------------------------+
        //+     VORGEHEN :                                                      |
        //+     Liste abarbeiten, Teilstring bis " " ermitteln,                 |
        //+     Variablen name = Teilstring --> 2. Teilstring in Wert wandeln   |
        //+     und in der s3DStruct zuweisen                                   |
        //+---------------------------------------------------------------------+

        for (uint i = 0; i < cfg.size(); i++) {
            std::vector<std::string> parts = split(cfg.at(i), SPACE);

            if (parts.at(0) == "originX")
                d3s.origin.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "originY")
                d3s.origin.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "originZ")
                d3s.origin.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorRed")
                d3s.color.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorGreen")
                d3s.color.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorBlue")
                d3s.color.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorAlpha")
                d3s.color.w = StringToFloat(parts.at(1));

            if (parts.at(0) == "hasLight")
                d3s.hasLight = StringToInt(parts.at(1));

            if (parts.at(0) == "textures")
                d3s.textures = parts.at(1);

            if (parts.at(0) == "translateX")
                d3s.trans.translate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateY")
                d3s.trans.translate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateZ")
                d3s.trans.translate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateX")
                d3s.trans.rotate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateY")
                d3s.trans.rotate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateZ")
                d3s.trans.rotate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleX")
                d3s.trans.scale.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleY")
                d3s.trans.scale.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleZ")
                d3s.trans.scale.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "firstTranslate")
                d3s.firstTranslate = StringToInt(parts.at(1));

            if (parts.at(0) == "texture0")
                d3s.texture0 = parts.at(1);

            if (parts.at(0) == "texture1")
                d3s.texture1 = parts.at(1);

            if (parts.at(0) == "texture2")
                d3s.texture2 = parts.at(1);

            if (parts.at(0) == "texture3")
                d3s.texture3 = parts.at(1);

            if (parts.at(0) == "texture4")
                d3s.texture4 = parts.at(1);

        }
        return true;

    }
    return false;
}

bool CEngine::initButtonStruct(sButtonStruct &bs, std::vector<std::string> cfg) {

    if (cfg.size() >= CFG_BUTTON_SIZE ) {
        bs.path = getValueItem(cfg[0],"Image: ");
        loginfo("Image Path: "+ bs.path);

        bs.PosX = StringToFloat(getValueItem(cfg[1],"PositionX: "));

        bs.PosY = StringToFloat(getValueItem(cfg[2],"PositionY: "));

        bs.SizeX =  StringToFloat(getValueItem(cfg[3],"SizeX: "));

        bs.SizeY =  StringToFloat(getValueItem(cfg[4],"SizeY: "));

        bs.Enable = StringToInt(getValueItem(cfg[5],"Enable: "));

        bs.ImageRed = StringToFloat(getValueItem(cfg[6],"BGRed: "));

        bs.ImageGreen = StringToFloat(getValueItem(cfg[7],"BGGreen: "));

        bs.ImageBlue = StringToFloat(getValueItem(cfg[8],"BGBlue: "));

        bs.TextRed = StringToFloat(getValueItem(cfg[9],"TextColorRed: "));

        bs.TextGreen = StringToFloat(getValueItem(cfg[10],"TextColorGreen: "));

        bs.TextBlue = StringToFloat(getValueItem(cfg[11],"TextColorBlue: "));

        return true;
    }
    else
        return false;
}





