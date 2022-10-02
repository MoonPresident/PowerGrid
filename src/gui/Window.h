#include "callbacks.h"
#include "my_debug.h"

#include <iostream>

//Initial setup for window.
#define WINDOW_TITLE "PowerGrid"
#define INITIAL_WIDTH 960
#define INITIAL_HEIGHT INITIAL_WIDTH
#define INITIAL_X_OFF 800
#define INITIAL_Y_OFF 50

#define debug

//TODO: Abstract callback information and put it into its own class.
class Window {
private:
    GLFWwindow* window;
public:
    
    Window() {
        srand(time(NULL));
        resetLeftClickFlag();
        resetRightClickFlag();
        setScrollFlag(10);
        
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
            INITIAL_WIDTH,
            INITIAL_HEIGHT,
            WINDOW_TITLE,
            NULL, //glfwGetPrimaryMonitor(), //<- does fullscreen
            NULL
        );
        
        glfwSetWindowPos(window, INITIAL_X_OFF, INITIAL_Y_OFF);
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
    
    GLFWwindow* getWindow() {
        return window;
    }
};