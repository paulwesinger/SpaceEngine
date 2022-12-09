/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   defines.h
 * Author: paul
 *
 * Created on 05. Jänner 2019, 13:04
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <chrono>

typedef void (*FP)();  // Zeiger auf Funktion wird für eventhandling gebraucht
typedef void (*FPB)(bool);
typedef std::chrono::high_resolution_clock Clock;


const int MAX_SCHEMES = 6;   // siehe COLOR_SCHEMES
const std::string NO_FILE  = "NO FILE";


// Structs for Objects to read in
enum ObjectType {
    ZYLINER = 0 ,
    KUGEL       ,
    ECK4        ,
    ECK6        
};


enum COLOR_Sheme {
    DARK = 0,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    SYSTEM
};

enum LineType {
    DASHED       = 0,
    POINT,
    SOLID
};


typedef struct {

    float x;
    float y;
    float z;
 }structCadBase;


typedef struct {
    glm::vec3 vector;
    glm::vec3 color;
    glm::vec2 tex;
} sVertexTexture ;

typedef struct {
    glm::vec3 vector;
    glm::vec3 normals;
    glm::vec3 color;
    glm::vec2 tex;
} sVertexNormals ;

typedef struct {
    glm::vec3 vector;
    glm::vec3 color;
} sVertexColor;


typedef struct {
 int x;
 int y;
 int x1;
 int y1;
} sRect;

typedef struct {
  int x;
  int y;
 // sPoint(int _x, int _y) :  x(_x), y(_y)  {}

}sPoint;

struct POINT {

    float x;
    float y;
    float z = 0.0f;

    POINT(float _x, float _y) :  x(_x), y(_y)  {}
};
typedef struct POINT Point;

struct sSize {
    int w;
    int h;
} ;

typedef struct _float2{
    float x;
    float y;
} FLOAT2;

typedef struct _float3{
    float x;
    float y;
    float z;
}FLOAT3;

typedef struct _float4{
    float x;
    float y;
    float z;
    float w;
}FLOAT4;

typedef struct {
    float x;
    float y;
    float z;
} VECTOR;

typedef struct _2D{
    long id;
    float x;
    float y;
}VECTOR2D;

typedef struct _3D{
    long id;
    _float3 vector;
    _float3 normale;
}VECTOR3D;

typedef struct _transform {
    _float3 translate;
    _float3 rotate;
    _float3 scale;
}TRANSFORM;

typedef struct _face {
    short p0;
    short p1;
    short p2;
}FACE;

typedef struct{
    float u;
    float v;
}TEXTURECOORDS;

typedef struct _color{
    _float4 color;
}COLOR;

typedef struct _material{
    _float3 ambient;
    _float3 diffuse;
    _float3 specular;
    float shiness;
} MATERIAL;

// Header for global defines 
// Mouse 
typedef struct {
    int lastx,x;
    int lasty,y;
} MOUSE;

/*
enum Events{

    NO_INPUT                = 0,
    MOUSE_Move,
    // Input Key
    KEY_Esc,                 
    KEY_Left,               
    KEY_Right,               
    KEY_Up   ,               
    KEY_Down ,    
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    // A S D E  für rotate Camera 
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_E,
    KEY_Q,  // Stop animation
    //ortho bzw perspective mode:
    KEY_O,
    KEY_P,
    // Wired or Textured
    KEY_W,
    KEY_T,   // TextureShader
    KEY_C,   //ColorShader
    // Show-Hide Menu
    KEY_M,
    // Controll Camera Speed
    NUM_PLUS,
    NUM_MINUS,

    KEY_F1          = 500,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    MOUSE_Move_Right = 1000,
    MOUSE_Move_Left ,         
    MOUSE_Move_Up,      
    MOUSE_Move_Down,

    MOUSE_BTN_Left_DOWN   = 10000 ,
    MOUSE_BTN_Right_DOWN ,
    MOUSE_BTN_MiddLe_DOWN,

    MOUSE_BTN_Left_UP   = 11000 ,
    MOUSE_BTN_Right_UP ,
    MOUSE_BTN_MiddLe_UP,

    MOUSE_Wheel 
};
*/

enum ShaderType {
    COLOR_SHADER = 0,
    TEXTURE_SHADER,
    LIGHT_SHADER,
    LIGHT_COLOR_SHADER,
    LIGHT_TEXTURE_SHADER,
    GLASS_SHADER
};

// ------------------------------------------------------
// needed for loading 2D and 3D objects from a file
// ------------------------------------------------------
typedef struct {

    bool firstTranslate;
    bool hasLight;
    TRANSFORM trans;
    FLOAT3 origin;
    FLOAT4 color;
    std::string textures;// for list

    std::string texture0;
    std::string texture1;
    std::string texture2;
    std::string texture3;
    std::string texture4;

}s3DStruct;

// ------------------------------------------------------
// needed for loading 2D and 3D objects from a file
// ------------------------------------------------------
typedef struct {

    bool firstTranslate;
    bool hasLight;
    TRANSFORM trans;
    FLOAT3 origin;
    FLOAT4 color;
    std::string textures;// for list

    std::string texture0;
    std::string texture1;
    std::string texture2;
    std::string texture3;
    std::string texture4;

    float radius;
    int meshpoints;

}sSphereStruct;

typedef  struct {
    int patchX;
    int patchZ;
    float rasterX;
    float rasterZ;
    std::string textures;
    std::string texture0;
    std::string texture1;
    std::string texture2;
    std::string texture3;
    std::string texture4;
    FLOAT4 color;
    TRANSFORM trans;
    bool hasLight;
}sLandscape ;


#endif /* DEFINES_H */

