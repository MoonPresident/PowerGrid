/**
 * @file displayObject.h
 * @author MoonPresident
 * @date October 25th 2020
 * 
 * A class for any object that will be displayed on screen.
 */

//Include this everywhere
#include "my_debug.h"

#ifndef DISPLAY_OBJECT_H
#define DISPLAY_OBJECT_H

#include <chrono>
#include <ratio>
#include <functional>
#include <vector>

#include "glad/glad.h"
#include "glfw3.h"
#include "glm.hpp"
#include "ShaderStore.h"

class WorldData;

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
    
    time_point<steady_clock> creation_timestamp;
    
    std::function<void (WorldData&, DisplayObject&)> movement_behaviour;
    std::function<bool (DisplayObject&, DisplayObject&)> collision_detection;
    std::function<bool (DisplayObject&)> lifecycle_conditions;
    
    DisplayObject() {
        creation_timestamp = steady_clock::now();
        for(int i = 0; i < 4; i++) real_location[i] = 0.f;
    }
    
    void setLocation(GLfloat source[4], GLfloat scale[4]) {
        for(int i = 0; i < 4; i++) real_location[i] = source[i];
        for(int i = 0; i < 4; i++) location[i] = source[i] * scale[i];
    }
};

 #endif /* DISPLAY_OBJECT_H */