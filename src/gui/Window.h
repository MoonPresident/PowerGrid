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
    Window();
    Window::~Window();
    GLFWwindow* getWindow();
};