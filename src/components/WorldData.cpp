#include "WorldData.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

/**
 * @brief constructor
 */
WorldData::WorldData() {
    //Set up time step and fps timestamp
    fps = 0;
    current_timestamp = steady_clock::now();
    previous_timestamp = current_timestamp;
    fps_timestamp = current_timestamp;
    
    mousePitch = 0.f;
    mouseYaw = -90.f;
    sensitivity = 0.1f;
};

/**
 * @brief destructor
 */
WorldData::~WorldData() {
    glDeleteBuffers(1, &worldVAO);
};

/**
 * @brief Set current time stamp
 */
void WorldData::set_timer() {
    current_timestamp = steady_clock::now();
};

/**
 * @brief Calculate timestep.
 * @return Timestep
 */
int WorldData::get_delta_t() {
    previous_timestamp = current_timestamp;
    current_timestamp = steady_clock::now();
    
    return duration_cast<microseconds>(current_timestamp - previous_timestamp).count();
};


/**
 * @brief Triggers fps handling
 * @return fps if its available, 0 otherwise.
 */
int WorldData::check_fps() {
    auto delta_fps = duration_cast<seconds>(current_timestamp - fps_timestamp).count();
    auto fps_output = 0;
    
    if(delta_fps) {
        fps_timestamp = current_timestamp;
        fps_output = fps;
        fps = 0;
    }
    
    fps++;
    return fps_output;
};

//Note: need to pick when to scale things. The trouble comes from the fact that OpenGL considers the frame to be a square.


/**
 * @brief Gets the cursor position and translates it into a float
 */
void WorldData::getCursorPosition() {
    glfwGetCursorPos(window.getWindow(), cursor_position, cursor_position + 1);
    
    cursor_position[1] = (2 * (cursor_position[1] / (float) height) - 1) * x_scale;
    cursor_position[0] = (2 * (cursor_position[0] / (float) width) - 1) * y_scale;
};

/**
 * @brief Get the bearing from an object to the cursor.
 * @param location
 * @return 
 */
//Normalise because the frame treats a rectangle as a square for angles (45 degree corners).
float WorldData::getBearingToCursor(float location[]) {
    float x_span = cursor_position[1] + location[1] * x_scale;
    float y_span = cursor_position[0] - location[0] * y_scale;
    
    return (float) atan(x_span / y_span) + (y_span < 0) * M_PI;
};




float WorldData::getBearing2D(float source[], float target[]) {
    float x_span = 0 - (target[1] - source[1]) * x_scale;
    float y_span = (target[0] - source[0]) * y_scale;
    
    return (float) atan(x_span / y_span) + (y_span < 0) * M_PI;
};

void WorldData::setScale(float source[]) {
    for(int i = 0; i < 4; i++) scale[i] = source[i];
};

void WorldData::calculate_timestep() {
    getCursorPosition();
};

void WorldData::run() {
    std::cout << "running "; 
}

//Mouse handler
void WorldData::setMouseYaw(float _x) {
    mouseYaw = _x;
}

void WorldData::setMousePitch(float _y) {
    mousePitch = _y;
}

float WorldData::getMouseYaw() {
    return mouseYaw;
}

float WorldData::getMousePitch() {
    return mousePitch;
}