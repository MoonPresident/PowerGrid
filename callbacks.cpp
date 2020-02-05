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


//Keyboard callback
int lastKey, lastAction;
void general_keyboard_callback(
        GLFWwindow* window, int key, int scancode, int action, int mods
) {
    cout << "Key: " << key << (char) key << ", Scancode: " << scancode << endl;
    cout << "Action: " << action << ", mods: " << mods << endl;
    switch(key) {
        case 'w':
            
        case 'a':
        
        case 's':
        
        case 'd':
            break;
    }
}


//Flags
int mousebuttonFlag;

void mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods) {
    if(action) {
        cout  << "Button: " << button << "Action: " << action  << "Mods: " <<  mods << endl << endl;
        mousebuttonFlag = 1;
    }
}

int getMousebuttonFlag() {
    return mousebuttonFlag;
}

void setMousebuttonFlag(int val) {
    mousebuttonFlag = val;
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
    glfwSetKeyCallback(window, general_keyboard_callback);
}