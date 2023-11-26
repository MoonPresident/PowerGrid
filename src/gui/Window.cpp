/**
 * @file Window.cpp
 * @author MoonPresident
 * @date December 21st 2022
 * 
 * Window for simulation
 */

#include "Window.h"

#include "callbacks.h"
#include "my_debug.h"

#include <iostream>
#include <ctime>

//Initial setup for window.
#define WINDOW_TITLE "PowerGrid"
enum INITIAL {
    WIDTH = 960,
    HEIGHT = 960,
    X_OFF = 800,
    Y_OFF = 50
};

Window::Window() {
    //TODO relocate.
    srand(time(nullptr));
    resetLeftClickFlag();
    resetRightClickFlag();
    setScrollFlag(10);
    //END TODO
    
    if (!glfwInit()) exit(EXIT_FAILURE);
    
    #ifdef debug
    std::cout << "glfw init successful" << std::endl;
    #endif
    
    //Set up error callback.
    glfwSetErrorCallback(basic_error_callback);
    
    //Set up multisampling
    glfwWindowHint(GLFW_SAMPLES, 8);
    
    //Set OpenGL version.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    
    window = glfwCreateWindow(
        INITIAL::WIDTH,
        INITIAL::HEIGHT,
        WINDOW_TITLE,
        nullptr, //glfwGetPrimaryMonitor(), //<- does fullscreen
        nullptr
    );
    
    glfwSetWindowPos(window, INITIAL::X_OFF, INITIAL::Y_OFF);
    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Glad crashed. Exiting." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    #ifdef debug
    std::cout << "Glad loaded." << std::endl;
    #endif
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

auto Window::getWindow() -> GLFWwindow* {
    return window;
}