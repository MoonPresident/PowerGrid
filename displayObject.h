/**
 * @file displayObject.h
 * @author MoonPresident
 * @date October 25th 2020
 * 
 * A class for any object that will be displayed on screen.
 */

//Include this everywhere
#include "debug.h"

#ifndef DISPLAY_OBJECT_H
#define DISPLAY_OBJECT_H

#include <chrono>
#include <ratio>
#include <functional>

//#include "WorldData.h"
class WorldData;
class DisplayObject;

using namespace std::chrono;

/**
 * @class DisplayObject
 * @author ThomasSebastian
 * @date 16/11/2020
 * @file DisplayObject.h
 * @brief This class handles the data for a single openGL program
 */

class DisplayObject {
public:
    Program program;
    GLfloat location[4];
    GLfloat real_location[4];
    float radians;
    std::function<void (WorldData, DisplayObject&)> movement_behaviour;
    
    DisplayObject() {
        for(int i = 0; i < 4; i++) real_location[i] = 0.f;
    }
    
    void setLocation(GLfloat source[4], GLfloat scale[4]) {
        for(int i = 0; i < 4; i++) real_location[i] = source[i];
        for(int i = 0; i < 4; i++) location[i] = source[i] * scale[i];
    }
};

 #endif /* DISPLAY_OBJECT_H */