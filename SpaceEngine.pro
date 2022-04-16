QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix:LIBS += -L /usr/lib64 -L/usr/lib64/GL -lGL -lSDL2 -lGLEW -lSDL2_image -lfreetype
#-lIrrKlang
#-L/usr/lib64/irrklang
SOURCES += \
        3DLoader/load3ds.cpp \
        Animate/animate.cpp \
        base2d/base2d.cpp \
        baseobject/baseobject.cpp \
        buttons/button.cpp \
        camera/camera.cpp \
        checkbox/checkbox.cpp \
        cockpit/cockpit.cpp \
        colors/colorscheme.cpp \
        controllcontainer/controllcontainer.cpp \
        cube/colorcube.cpp \
        cube/cube.cpp \
        engine/engine.cpp \
        fileutils/fileutil.cpp \
        imageloader/loadimage.cpp \
        initgl.cpp \
        landscape/landscape.cpp \
        lights/light.cpp \
        logs/logs.cpp \
        main.cpp \
        menu/menu.cpp \
        meshobject/meshobject.cpp \
        objectclasses/object.cpp \
        objloader/objloader.cpp \
        particleengine/partikelengine.cpp \
        plane3D/plane3D.cpp \
        projection/projection.cpp \
        shaders/shader.cpp \
        signals/signal.cpp \
        skybox/skybox.cpp \
        sphere/sphere.cpp \
        textedit/textedit.cpp \
        textrenderer/textrender.cpp \
        utils/utils.cpp \
        vecmath/vecmath.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    OzEngine/OzEngine.pro \
    Ozengine.pro

DISTFILES += \
    BtnInstances/Button0.txt \
    BtnInstances/Button2.txt \
    Description.txt \
    Meshes/85-cottage_obj.zip \
    Meshes/85-cottage_obj/cottage_obj.mtl \
    Meshes/Kiste.3ds \
    Meshes/Quad.mtl \
    Meshes/spaceship.3ds \
    README.md \
    ShaderSources/FogShaderExample.txt \
    ShaderSources/FragmentTextureLightShader.frg \
    ShaderSources/VertexTextureLightShader.vex \
    ShaderSources/colorshader.frg \
    ShaderSources/cubefragmentshaderMulti.frg \
    ShaderSources/cubefragmentshaderMultinormals.frg \
    ShaderSources/cubevertexnormalshader.vex \
    ShaderSources/cubevertexshader.vex \
    ShaderSources/fogfragmentshader.frg \
    ShaderSources/fogvertexshader.vex \
    ShaderSources/fragmentnormalcolorshader.frg \
    ShaderSources/glasshader.frg \
    ShaderSources/glasshader.vex \
    ShaderSources/vertexnormalcolorshader.vex \
    config/2DObjects/2DObjects.txt \
    config/3DObjects/ColoredCubes/ColorCubes.cfg \
    config/3DObjects/ColoredCubes/Cube1.txt \
    config/3DObjects/ColoredCubes/Cube2.txt \
    config/3DObjects/ColoredCubes/Cube3.txt \
    config/3DObjects/Landscapes/Land1.txt \
    config/3DObjects/Landscapes/Landscapes.cfg \
    config/3DObjects/TexturedCubes/Cube1.txt \
    config/3DObjects/TexturedCubes/Cube2.txt \
    config/3DObjects/TexturedCubes/Cube3.txt \
    config/3DObjects/TexturedCubes/Cube4.txt \
    config/3DObjects/TexturedCubes/Cube5.txt \
    config/3DObjects/TexturedCubes/TexCubes.cfg \
    config/Buttons/Button1.txt \
    config/Buttons/Button2.txt \
    config/Buttons/Button3.txt \
    config/Buttons/ButtonList.cfg \
    config/Engine/engine.cfg \
    config/LandTextures.cfg \
    config/SphereWorldTextures.cfg \
    config/cube2textures.cfg \
    config/cube3textures.cfg \
    config/cube5textures.cfg \
    config/cubetextures.cfg \
    fonts/DroidSans.ttf \
    icons/256x256/vlc.png \
    icons/QtProject-qtcreator.png \
    icons/chromium-browser.png \
    icons/ekiga.png \
    icons/gnome-color-manager.png \
    icons/google-chrome.png \
    icons/hb-icon.png \
    icons/ibus-hangul.png \
    icons/ibus-setup-hangul.png \
    icons/linguist.png \
    icons/preferences-color.png \
    icons/smplayer.png \
    images/Add.png \
    images/Add.xcf \
    images/Andromeda200x150.png \
    images/Bottom.png \
    images/Bottom.xcf \
    images/ButtonBG.png \
    images/ButtonBG.xcf \
    images/ButtonBGPressed.xcf \
    images/ButtonPressed.png \
    images/ButtonReleased.png \
    images/Color.png \
    images/Color.xcf \
    images/ControllBg.png \
    images/DrawMode.xcf \
    images/Drawmode.png \
    images/Headline.png \
    images/Headline.xcf \
    images/Lines.png \
    images/Lines.xcf \
    images/NewCube.png \
    images/NewCube.xcf \
    images/Points.png \
    images/Points.xcf \
    images/Rahmen.xcf \
    images/ShowSkyBox.png \
    images/ShowSkyBox.xcf \
    images/Textfeld.png \
    images/Textfeld.xcf \
    images/Textfeld_neu.xcf \
    images/Texture.png \
    images/Textured.xcf \
    images/ToogleSkybox.png \
    images/ToogleSkybox.xcf \
    images/button_green.png \
    images/button_green.xcf \
    images/button_white.png \
    images/darkgray.png \
    images/error.png \
    images/errorAlpha.png \
    images/free-vector-web-buttons-30.jpg \
    images/redButton.png \
    images/set-of-colorful-web-buttons-vector-1539551.jpg \
    images/wall.png \
    images/wallAlpha.png \
    images/world-map-1748403__340.webp \
    images/world.png \
    master/README.md \
    skybox/desert/desert_bk.tga \
    skybox/desert/desert_dn.tga \
    skybox/desert/desert_ft.tga \
    skybox/desert/desert_lf.tga \
    skybox/desert/desert_rt.tga \
    skybox/desert/desert_up.tga \
    skybox/orbital/orbital-element_bk.tga \
    skybox/orbital/orbital-element_dn.tga \
    skybox/orbital/orbital-element_ft.tga \
    skybox/orbital/orbital-element_lf.tga \
    skybox/orbital/orbital-element_rt.tga \
    skybox/orbital/orbital-element_up.tga \
    sounds/MF-3DAYS.S3M \
    sounds/MF-PANTS.MOD \
    sounds/MF-W-90.XM \
    sounds/bell.wav \
    sounds/explosion.wav \
    sounds/getout.ogg \
    sounds/license.txt \
    sounds/ophelia.mp3

HEADERS += \
    3DLoader/load3ds.h \
    Animate/animate.h \
    base2d/base2d.h \
    baseobject/baseobject.h \
    buttons/button.h \
    camera/camera.h \
    checkbox/checkbox.h \
    cockpit/cockpit.h \
    colors/colorscheme.h \
    controllcontainer/controllcontainer.h \
    cube/colorcube.h \
    cube/cube.h \
    defaults.h \
    defines.h \
    engine/engine.h \
    fileutils/fileutil.h \
    functions.h \
    imageloader/loadimage.h \
    initgl.h \
    landscape/landscape.h \
    lights/light.h \
    logs/logs.h \
    menu/menu.h \
    meshobject/meshobject.h \
    objectclasses/object.h \
    objloader/objloader.h \
    particleengine/partikelengine.h \
    plane3D/plane3D.h \
    projection/projection.h \
    shaders/shader.h \
    signals/signal.h \
    skybox/skybox.h \
    sphere/sphere.h \
    textedit/textedit.h \
    textrenderer/textrender.h \
    utils/utils.h \
    vecmath/vecmath.h
