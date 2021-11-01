#ifndef OBJECT_H
#define OBJECT_H


/*
 * File:   object.h
 * Author: paul
 *
 * Created on 12. April 2019, 14:31
 */

#include <string>
#include <vector>
#include "../defines.h"
#include "../fileutils/fileutil.h"

//***************************************************
// Basisklasse für allle Objecttypen
// beinhaltet informationen über
// Transform,Texture,Material,...
// .. und eine 2D Punktliste aus einem Objectfile.
// daraus weird dann ein zylinder,kugel, generieret
class Object {
public:
    Object();
    Object(const Object& orig);
    virtual ~Object();
    virtual bool Load(std::string datei) = 0;

    std::string GetName();
    std::string GetPah2Texture();

protected:
    MATERIAL GetMaterial();
    COLOR GetColor();

    //virtual void Text(std::string t="");
private:
    std::string _Name;
    std::string _TexturePath;
    MATERIAL _Material;
    std::vector<VECTOR2D> list2D;  // Die 2D Punkte, aus denen dann ds Object in den Unterklassen erstellt wird
    COLOR _Color;
};

// ***********************************
// Unterklassen
// -----------------------------------

class Zylindrisch : public Object {
public:
    Zylindrisch(std::string datei);
    virtual ~Zylindrisch();

    std::vector<VECTOR3D> & GetVeklist();
    std::vector<FACE> & GetFacelist();

    bool Load(std::string datei);

private:
    std::vector<VECTOR3D> veklist;
    std::vector<FACE> facelist;
    ObjectType _Type;
    std::string filename;

};

#endif // OBJECT_H
