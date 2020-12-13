/**
 * @file displayObject.h
 * @author MoonPresident
 * @date October 25th 2020
 * 
 * A class for any object that will be displayed on screen.
 */

//Include this everywhere
#include "my_debug.h"
#include "glad/glad.h"
#include "glfw3.h"

#ifndef VIRTUAL_OBJECT_H
#define VIRTUAL_OBJECT_H

#include <chrono>
using namespace std::chrono;

class VirtualObject {
public:
    Program program;
    GLfloat location[4];
    float radians;
    
    DisplayObject() {
        for(int i = 0; i < 4; i++) location[i] = 0.f;
    }
};

class TransientObject: public DisplayObject {
public:
    time_point<steady_clock> end;
    
    TransientObject(time_point<steady_clock> _end) {
        end = _end;
    }
    
    void setEnd(time_point<steady_clock> _end) {
        end = _end;
    }
};

#endif /* VIRTUAL_OBJECT_H */