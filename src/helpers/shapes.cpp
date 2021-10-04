/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * These function use openGL primitive. There are plans to add VBO and VAO versions later.
 */

#include "glad/glad.h"
#include "glfw3.h"

#define ARRAY_2D 2
#define ARRAY_COLOR 3


//void hardCodedTriangle() {
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.f, 0.f, 0.f);
//    glVertex3f(-0.6f, -0.4f, 0.f);
//    glColor3f(0.f, 1.f, 0.f);
//    glVertex3f(0.6f, -0.4f, 0.f);
//    glColor3f(0.f, 0.f, 1.f);
//    glVertex3f(0.f, 0.6f, 0.f);
//    glEnd();
//}