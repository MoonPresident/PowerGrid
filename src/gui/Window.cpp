#include "Window.h"

Window::Window() {
    //TODO relocate.
    srand(time(NULL));
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

GLFWwindow* Window::getWindow() {
    return window;
}