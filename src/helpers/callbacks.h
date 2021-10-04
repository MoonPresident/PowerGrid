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

//TODO: find a better way to handle the massive chunk of globals in this file.

void basic_error_callback(int error, const char* description);

void close_on_unfocus(GLFWwindow* window, int focused);

void general_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods);

int getLeftClickFlag();

void resetLeftClickFlag();

int getRightClickFlag();

void resetRightClickFlag();

int getScrollFlag();

void setScrollFlag(int val);


//Mouse callbacks
float getMouseOffsetX();
float getMouseOffsetY();
float getMouseLastX();
float getMouseLastY();

void setMouseOffsetX(float _x);
void setMouseOffsetY(float _y);
void setMouseLastX(float _x);
void setMouseLastY(float _y);

//void mouse_callback(GLFWwindow* window, double xpos, double ypos);


//Callback setter
void setCallbacks(GLFWwindow* frame);


#endif /* CALLBACKS_H */