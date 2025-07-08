/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * Stores callbacks for GLFW functions.
 */

#ifndef MOUSE_H

//Mouse callbacks
double getMouseOffsetX();
double getMouseOffsetY();
double getMouseLastX();
double getMouseLastY();

void setMouseOffsetX(double _x);
void setMouseOffsetY(double _y);
void setMouseLastX(double _x);
void setMouseLastY(double _y);

#endif /*MOUSE_H*/