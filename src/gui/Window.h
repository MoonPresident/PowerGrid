/**
 * @file Window.h
 * @author MoonPresident
 * @date December 21st 2022
 * 
 * Window for simulation
 */

#ifndef WINDOW_H

struct GLFWwindow;

//TODO: Abstract callback information and put it into its own class.
class Window {
private:
    GLFWwindow* window;
public:
    Window();
    ~Window();
    GLFWwindow* getWindow();
    // void handleInputs();
};

#endif /* WINDOW */