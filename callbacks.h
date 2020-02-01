/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * Stores callbacks for GLFW functions.
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H

void basic_error_callback(int error, const char* description);

void close_on_unfocus(GLFWwindow* window, int focused);

void mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods);

int getMousebuttonFlag();

void setMousebuttonFlag(int val);

#endif /* CALLBACKS_H */