#include "object.h"


/*
 * File:   object.cpp
 * Author: paul
 *
 * Created on 12. April 2019, 14:31
 */

#include "object.h"
#include "../logs/logs.h"

using namespace std;

Object::Object() {

}

Object::Object(const Object& orig) {
}

Object::~Object() {
}

string Object::GetName()            { return _Name; }
string Object::GetPah2Texture()     { return _TexturePath; }

MATERIAL Object::GetMaterial()      { return _Material; }
COLOR    Object::GetColor()         { return _Color;    }


// **************************************
// Unterklassen
// --------------------------------------

Zylindrisch::Zylindrisch(string datei) {
   filename = datei;
   Load(filename);
}
Zylindrisch::~Zylindrisch() {
}

bool Zylindrisch::Load(string datei) {
    fileUtil * fu = new fileUtil();
    //fu ->readLine(datei.c_str())  ;
    delete fu;
    return true;
}

vector<VECTOR3D> & Zylindrisch::GetVeklist() {
    return veklist;
}
vector<FACE> & Zylindrisch::GetFacelist() {
    return facelist;
}
