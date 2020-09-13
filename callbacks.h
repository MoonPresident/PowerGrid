/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * Stores callbacks for GLFW functions.
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "glad/glad.h"
#include "glfw3.h"

void basic_error_callback(int error, const char* description);

void close_on_unfocus(GLFWwindow* window, int focused);

void general_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods);

int getMousebuttonFlag();

void setMousebuttonFlag(int val);

int getScrollFlag();

void setScrollFlag(int val);

void setCallbacks(GLFWwindow** frame);

#endif /* CALLBACKS_H */