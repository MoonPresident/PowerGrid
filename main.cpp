/**
 * Author: MoonPresident
 * Date: May 4th 2020
 * 
 * 
 * 
 * Needs links included to opengl32 and gdi32
 * Get GLM installed. Or make your own vector math, up to you.
 */
 
 //https://www.glprogramming.com/red/chapter02.html
 //https://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/opengl_programming.html

#include "main.h"


#define DEV

#define ARRAY_2D 2
#define ARRAY_COLOR 3


//NEXT STEP:
//Move using WASD, shoot something, and get a menu going.
//For the Menu: find out what is needed to get characters up and going. May need bitmaps.


namespace Frame {
    int width {1280};
    int height = 960;
    const char* title = "PowerGrid";
}

/**
 * @brief 
 * @param frame
 */
void setCallbacks(GLFWwindow** frame) {
    GLFWwindow* window = *frame;
    
    glfwMakeContextCurrent(window);
    glfwSetWindowFocusCallback(window, close_on_unfocus);
    glfwSetMouseButtonCallback(window, mousebutton_flag_callback);
}





void startup(GLFWwindow** window);

int main(int argc, char **argv) {
    srand(time(NULL));
    
    setMousebuttonFlag(0);
    //The way startup is currently included is janky as hell.
    //TODO: Fix implementation of startup sequence.
    
    
    //Run code
    
    
    #ifdef DEV
    GLFWwindow* window;
    startup(&window);
    
    GLfloat vertices[3][2];
    for(int i = 0; i < 3; i++) {
        vertices[i][0] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2)) - 1;
        vertices[i][1] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2)) - 1;
    }
    
    Shape2D<3> triangle = Shape2D<3>(vertices);
    
    setCallbacks(&window);
    
    float radius = 0.4f;
    Shape2D<4> square = equilateralShape<4>(radius);
    
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        
        
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height + 1;
        
        //Sets the viewport, first 2 car's specify the bottom right hand corner
        glViewport(0, 0, width, height);
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        
        glBegin(GL_QUADS);
        
        square.drawShape();
        
        glEnd();
        
        glfwSwapBuffers(window);
        
//        if(getMousebuttonFlag()) {
//            setMousebuttonFlag(0);
//            
//            for(int i = 0; i < 3; i++) {
//                vertices[i][0] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2)) - 1;
//                vertices[i][1] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2)) - 1;
//            }
//            
//            
//            triangle = Shape2D<3>(vertices);
//        }
        
        
    }
    
    #else
    //Triangle Example: basic run sequence
    triangle_example();
    #endif
    
    //Close up shop
    glfwTerminate();
	return 0;
}



void startup(GLFWwindow** window) {
    
    if (!glfwInit()) exit(EXIT_FAILURE);
    
    glfwSetErrorCallback(basic_error_callback);
    
    *window = glfwCreateWindow(
        Frame::width,
        Frame::height,
        Frame::title,
        NULL, //glfwGetPrimaryMonitor(), //<- does fullscreen
        NULL
    );
    
    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}
