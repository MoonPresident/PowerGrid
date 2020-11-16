/**
 * @file displayObject.h
 * @author MoonPresident
 * @date October 25th 2020
 * 
 * A class for any object that will be displayed on screen.
 */

//Include this everywhere
#include "debug.h"

#include "DisplayObject.h"

#include "glad/glad.h"
#include "glfw3.h"

#ifndef BASIC_ENEMY_H
#define BASIC_ENEMY_H

#include <chrono>
using namespace std::chrono;

class BasicEnemy {
public:
    GLfloat location[4];
//    DisplayObject display;
    float moveSpeed;
    
    BasicEnemy() {
        for(int i = 0; i < 4; i++) location[i] = 0.f;
        moveSpeed = 0.001;
    }
    
    void handleMovement(auto delta_t, GLfloat target[]) {
        
    }
};



 #endif /* DISPLAY_OBJECT_H */