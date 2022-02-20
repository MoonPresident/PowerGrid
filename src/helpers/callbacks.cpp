/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * Stores callbacks for GLFW functions.
 */
 
#include "glad/glad.h"
#include "glfw3.h"
#include <iostream>

#include "my_debug.h"


void basic_error_callback(int error, const char* description){
    fputs(description, stderr);
}

void close_on_unfocus(GLFWwindow* window, int focused) {
    if(!focused) {
        glfwSetWindowShouldClose(window, 1);
    }
}

//Options for handling inputs:
//For Maximum scalability, scancodes are ideal, though it may be expediant 
//to use a combination of keys, characters and scancodes to optimise processing
//https://www.glfw.org/docs/3.3/input_guide.html#input_keyboard
//int keyboardFlags[256];
//Range: 108 inputs between 32 and 348 inclusive.


//Key input handling: input of 1 prepares a response, input of 2 adapts the response, input of 0 releases the response.
//Easiest way to differentiate between handling of since press and a long press: only fire off on the release.

void general_keyboard_callback(
        GLFWwindow* window, 
        int key, 
        int scancode, 
        int action, 
        int mods
) {
    
    #if defined debug_all || defined debug_mouse
    std::cout << "Key: " << key << (char) key << ", Scancode: " << scancode << std::endl;
    std::cout << "Action: " << action << ", mods: " << mods << std::endl;
    #endif
}


//Flags
int leftClickFlag;
int rightClickFlag;

void mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods) {
    if(action) {
        #ifdef debug_all
        std::cout  << "Button: " << button << "Action: " << action  << "Mods: " <<  mods << std::endl << std::endl;
        #endif
        if(button == 0) {
            leftClickFlag = 1;
        } else if(button == 1) {
            rightClickFlag = 1;
        }
    }
}

int getLeftClickFlag() {
    return leftClickFlag;
}

void resetLeftClickFlag() {
    leftClickFlag = 0;
}

int getRightClickFlag() {
    return rightClickFlag;
}

void resetRightClickFlag() {
    rightClickFlag = 0;
}


int scrollFlag;

int getScrollFlag() {
    return scrollFlag;
}

void setScrollFlag(int val) {
    if(val < 1) {
        scrollFlag = 1;
    } else {
        scrollFlag = val;
    }
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    scrollFlag += y_offset;
    if(scrollFlag < 1) scrollFlag = 1;
    
    #if defined debug_all || defined debug_mouse
    std::cout << "XY: " << x_offset << " " << y_offset << std::endl;
    #endif
}

double mouseOffsetX;
double mouseOffsetY;
double mouseLastX;
double mouseLastY;

double getMouseOffsetX()   { return mouseOffsetX; };
double getMouseOffsetY()   { return mouseOffsetY; };
double getMouseLastX()     { return mouseLastX; };
double getMouseLastY()     { return mouseLastY; };

void setMouseOffsetX(double _x)    { mouseOffsetX  = _x; };
void setMouseOffsetY(double _y)    { mouseOffsetY  = _y; };
void setMouseLastX(double _x)      { mouseLastX    = _x; };
void setMouseLastY(double _y)      { mouseLastY    = _y; };

bool firstMouse;
void mouse_callback(GLFWwindow* window, double xCoord, double yCoord) {
    if(!firstMouse) {   
        firstMouse = true;
        mouseOffsetX = xCoord;
        mouseOffsetY = yCoord;
        mouseLastX = xCoord;
        mouseLastY = yCoord;
    }
    mouseOffsetX = mouseLastX - xCoord;
    mouseOffsetY = mouseLastY - yCoord;
    mouseLastX = xCoord;
    mouseLastY = yCoord;
}

/**
 * @brief 
 * @param frame
 */
void setCallbacks(GLFWwindow* window) {
    firstMouse = false;
    
    glfwMakeContextCurrent(window);
    glfwSetWindowFocusCallback(window, close_on_unfocus);
    glfwSetMouseButtonCallback(window, mousebutton_flag_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, general_keyboard_callback);
    
    //Mouse callback
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
}