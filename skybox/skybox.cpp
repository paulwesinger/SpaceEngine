#include "skybox.h"

/*
 * File:   SkyBox.cpp
 * Author: paul
 *
 * Created on 08. Jänner 2019, 20:11
 */

#include<GL/glew.h>
//#include <glad.h>
#include "skybox.h"
#include <fstream>
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>

#include <glm/detail/type_mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../imageloader/loadimage.h"

// -------------------------
// Vertex Shader
// -------------------------

static const GLchar* skybox_VS_source =
{
    "#version 420 core                      \n"
    "layout (location = 0) in vec3 aPos;    \n"

    "out vec3 TexCoords;                    \n"
    "uniform mat4 projection;               \n"
    "uniform mat4 view;                     \n"

    "void main()                            \n"
    "{                                      \n"
    "   TexCoords = aPos;                   \n"
    "   gl_Position = projection * view * vec4(aPos, 1.0);\n"
    "}                                      \n"
};

static const GLchar * skybox_FS_source =
{
    "#version 330 core                      \n"
    "out vec4 FragColor;                    \n"

    "in vec3 TexCoords;                     \n"
    "uniform samplerCube skybox;            \n"

    "void main()                                                        \n"
    "{                                                                  \n"
    "   FragColor = texture(skybox, TexCoords);                         \n"
    "}                                                                  \n"
};
static float skyboxVertices[] = {
        // positions
        -500.0f,  500.0f, -500.0f,
        -500.0f, -500.0f, -500.0f,
         500.0f, -500.0f, -500.0f,
         500.0f, -500.0f, -500.0f,
         500.0f,  500.0f, -500.0f,
        -500.0f,  500.0f, -500.0f,

        -500.0f, -500.0f,  500.0f,
        -500.0f, -500.0f, -500.0f,
        -500.0f,  500.0f, -500.0f,
        -500.0f,  500.0f, -500.0f,
        -500.0f,  500.0f,  500.0f,
        -500.0f, -500.0f,  500.0f,

         500.0f, -500.0f, -500.0f,
         500.0f, -500.0f,  500.0f,
         500.0f,  500.0f,  500.0f,
         500.0f,  500.0f,  500.0f,
         500.0f,  500.0f, -500.0f,
         500.0f, -500.0f, -500.0f,

        -500.0f, -500.0f,  500.0f,
        -500.0f,  500.0f,  500.0f,
         500.0f,  500.0f,  500.0f,
         500.0f,  500.0f,  500.0f,
         500.0f, -500.0f,  500.0f,
        -500.0f, -500.0f,  500.0f,

        -500.0f,  500.0f, -500.0f,
         500.0f,  500.0f, -500.0f,
         500.0f,  500.0f,  500.0f,
         500.0f,  500.0f,  500.0f,
        -500.0f,  500.0f,  500.0f,
        -500.0f,  500.0f, -500.0f,

        -500.0f, -500.0f, -500.0f,
        -500.0f, -500.0f,  500.0f,
         500.0f, -500.0f, -500.0f,
         500.0f, -500.0f, -500.0f,
        -500.0f, -500.0f,  500.0f,
         500.0f, -500.0f,  500.0f
    };


SkyBox::SkyBox( glm::mat4 pro) {
    _SkyBoxID = -1;
    shader =  new (Shader);
    projection = pro;

    vs = shader->compileVertexShader( skybox_VS_source);
    fs = shader->compileFragmentShader(skybox_FS_source);
    loginfo ("Create Skybox Shader","Skybox");
    shaderprog = shader->CreateProgram(vs,fs);
    if ( shaderprog) {
        loginfo("Shader initaliesiert ID = " + IntToString(shaderprog),"Skybox::Skybox");
        skyboxLoaded = true;
    }
    else {
        skyboxLoaded = false; // War wohl nix, jetzt schon
        logwarn("Fatal : Shader nicht erstellt " ,"Skybox::SkyBox");

    }
}

SkyBox::SkyBox(const SkyBox& orig) {
    if (shaderprog)
        delete shader;
}

SkyBox::~SkyBox() {
    glDeleteBuffers(1,&skyboxVertexbuffer);
}

void SkyBox::SetProjection(glm::mat4 pro) {
    projection = pro;
}
void SkyBox::Draw( glm::mat4 cameraview) {

    glDepthFunc(GL_LEQUAL);
    glUseProgram(shaderprog);

    glBindVertexArray(skyboxVao);
    glBindTexture(GL_TEXTURE_CUBE_MAP,_SkyBoxID);
    glm::mat4 view = glm::mat4( glm::mat3(cameraview));

    viewlocation = glGetUniformLocation(shaderprog, "view");
    projlocation = glGetUniformLocation(shaderprog, "projection");

    glUniformMatrix4fv(viewlocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projlocation, 1, GL_FALSE, glm::value_ptr(projection));
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}
bool SkyBox::Load(std::vector<std::string> &faces) {
    if ( skyboxLoaded ) {

        // Skybox
        glGenVertexArrays(1, &skyboxVao);
        glGenBuffers(1,&skyboxVertexbuffer);
        glBindVertexArray(skyboxVao);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);

        if ( LoadCubeMap(faces)) {
            return true;
        }
        else
            return false;
    }
    return false;
}

bool SkyBox::LoadCubeMap(std::vector<std::string> &faces) {
    loginfo(" Loading Skybox images ....... ","Skybox::Load");
    glGenTextures(1,&_SkyBoxID);
    glBindTexture(GL_TEXTURE_CUBE_MAP,_SkyBoxID);

    for ( GLuint i = 0; i < faces.size(); i++ ) {
        SDL_Surface * surface;
        surface = CLoadImage::getSurface(faces[i].c_str(),"Skybox::LoadCubeMap");  //  IMG_Load(faces[i].c_str());
        if (surface->pixels )
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,GL_RGB, surface->w, surface->h,
            0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
            SDL_FreeSurface(surface);
            //logwarn("Face: " + faces[i] ,"Skybox::Load");
        }
        else {
            //logwarn("Konnte Image " + faces[i] + " nicht ladern ","Skybox::Load");
            skyboxLoaded = false; // Flag für späteres Draw....
        }
    }

    if ( skyboxLoaded ) {
        loginfo("Skybox()Cubemap geladen", " Skybox::Load");

        // Texture Filter
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        return true;
    }
    else
        logwarn("Fehler beim laden laden der CubeMAp: Ein(ige) Images konnten nicht geladen werden !!");

    return false;
}
