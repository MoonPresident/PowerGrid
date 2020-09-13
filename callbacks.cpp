/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * Stores callbacks for GLFW functions.
 */
 
#include "glad/glad.h"
#include "glfw3.h"
#include <iostream>


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
        GLFWwindow* window, int key, int scancode, int action, int mods
) {
    std::cout << "Key: " << key << (char) key << ", Scancode: " << scancode << std::endl;
    std::cout << "Action: " << action << ", mods: " << mods << std::endl;
//    switch(key) {
//        case 'w':
//            
//        case 'a':
//        
//        case 's':
//        
//        case 'd':
//            break;
//    }
}


//Flags
int mousebuttonFlag;

void mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods) {
    if(action) {
        std::cout  << "Button: " << button << "Action: " << action  << "Mods: " <<  mods << std::endl << std::endl;
        mousebuttonFlag = 1;
    }
}

int getMousebuttonFlag() {
    return mousebuttonFlag;
}

void setMousebuttonFlag(int val) {
    mousebuttonFlag = val;
}

int scrollFlag;

int getScrollFlag() {
    return scrollFlag;
}

void setScrollFlag(int val) {
    scrollFlag = val;
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    scrollFlag += y_offset;
    std::cout << "XY: " << x_offset << " " << y_offset << std::endl;
}




/**
 * @brief 
 * @param frame
 */
void setCallbacks(GLFWwindow** frame) {
    GLFWwindow* window = *frame;
    
    glfwMakeContextCurrent(window);
    glfwSetWindowFocusCallback(window, close_on_unfocus);
    glfwSetMouseButtonCallback(window, mousebutton_flag_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, general_keyboard_callback);
}