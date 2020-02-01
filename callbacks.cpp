/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * Stores callbacks for GLFW functions.
 */
 #include "main.h"

void basic_error_callback(int error, const char* description){
    fputs(description, stderr);
}

void close_on_unfocus(GLFWwindow* window, int focused) {
    if(!focused) {
        glfwSetWindowShouldClose(window, 1);
    }
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