/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vecmath.h
 * Author: paul
 *
 * Created on 01. Jänner 2019, 16:31
 */

#ifndef VECMATH_H__
#define VECMATH_H__

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "../defines.h"

void rotX(glm::vec3 & vec, float angle );  // degrees, no radians -> need to be converted !!
void rotY(glm::vec3 & vec, float angle );
void rotZ(glm::vec3 & vec, float angle );

void rotX(glm::vec3 & vec, double angle );  // degrees, no radians -> need to be converted !!
void rotY(glm::vec3 & vec, double angle );
void rotZ(glm::vec3 & vec, double angle );
// Kreis berechnungen für kartessisches 2D System:
void calccircle(float radius, float angle, glm::vec2 &point);
void calccircle(float radius, float angle, std::vector<glm::vec2> & l);
// other transforms later, if needed  ! 

void checkdegree(glm::vec3 & angle);
void checkdegree( float & angle); 
void checkdegree( double & angle); 

#endif /* VECMATH_H */

