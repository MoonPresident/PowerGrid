/**
 * Author: MoonPresident
 * Date: February 21st 2025
 * 
 * Stores callbacks for GLFW functions.
 */

//These are file scope, not global scope, so perhaps they should go in their
//own file so they are better isolated.
static double mouseOffsetX;
static double mouseOffsetY;
static double mouseLastX;
static double mouseLastY;

auto getMouseOffsetX() -> double   { return mouseOffsetX; }
auto getMouseOffsetY() -> double   { return mouseOffsetY; }
auto getMouseLastX() -> double     { return mouseLastX; }
auto getMouseLastY() -> double     { return mouseLastY; }

void setMouseOffsetX(double _x)    { mouseOffsetX  = _x; }
void setMouseOffsetY(double _y)    { mouseOffsetY  = _y; }
void setMouseLastX(double _x)      { mouseLastX    = _x; }
void setMouseLastY(double _y)      { mouseLastY    = _y; }

static bool firstMouse;

void mouse_callback(GLFWwindow* /*window*/, double xCoord, double yCoord) {
    if(!firstMouse) {   
        firstMouse = true;
        mouseOffsetX = xCoord;
        mouseOffsetY = yCoord;
        mouseLastX = xCoord;
        mouseLastY = yCoord;
    }
    mouseOffsetX = mouseLastX - xCoord;
    mouseOffsetY = mouseLastY - yCoord;
    mouseLastX = xCoord;
    mouseLastY = yCoord;
}