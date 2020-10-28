/**
 * @file main.cpp
 * @author MoonPresident
 * @date January 4th 2020
 * 
 * 
 * 
 * Needs links included to opengl32 and gdi32
 * Get GLM installed. Or make your own vector math, up to you.
 */

//https://www.glprogramming.com/red/chapter02.html
//https://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/opengl_programming.html
//https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects

/********************************************************************************
 *******                             Includes                             *******
 *******************************************************************************/
//Abstract functions
#include "callbacks.h"
#include "shapes.h"
#include "ShaderStore.h"
#include "player.h"
#include "WorldData.h"


//Includes
#include <fstream>

#define _USE_MATH_DEFINES
#include <cmath>

//My math library
#include "math.h"

#include "glad/glad.h"
#include "glfw3.h"


/********************************************************************************
 *******                           Namespaces                             *******
 *******************************************************************************/
using namespace std::chrono;

/********************************************************************************
 *******                             Defines                              *******
 *******************************************************************************/
 
//https://thebookofshaders.com/07/
#define SHADER_PATH         "..\\resources\\shaders\\"
#define SHADER_INDEX_FILE   "..\\resources\\shaders\\index.txt"

#define debug1

#define SQRT_2 1.4142

//GOALS ACHIEVED:
//  Square drawn and rotating with mouse
//  Movement with WASD

//NEXT STEP:
//Shoot something, and get a menu going.
//For the Menu: find out what is needed to get characters up and going. May need bitmaps.
//Print bitmaps
//Abstract out the drawing and the game logic


namespace Frame {
    int width  {960};//1280};
    int height  {960};
    int x_off   {800};
    int y_off     {50};
    const char* title = "PowerGrid";
}


//static GLuint create_buffer(GLenum target, const void* data, GLsizei buffer_size) {
//    GLuint buffer;
//    glGenBuffer(1, &buffer);
//    glBindBuffer(target, buffer);
//    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
//    return buffer;
//}


void startup(GLFWwindow** window) {
    
    srand(time(NULL));
    setMousebuttonFlag(0);
    setScrollFlag(10);
    
    if (!glfwInit()) exit(EXIT_FAILURE);
    
    #ifdef debug
    cout << "glfw init successful" << endl;
    #endif
    
    //Set up error callback.
    glfwSetErrorCallback(basic_error_callback);
    
    //Set up multisampling
    glfwWindowHint(GLFW_SAMPLES, 8);
    
    //Set OpenGL version.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    
    *window = glfwCreateWindow(
        Frame::width,
        Frame::height,
        Frame::title,
        NULL, //glfwGetPrimaryMonitor(), //<- does fullscreen
        NULL
    );
    
    glfwSetWindowPos(*window, Frame::x_off, Frame::y_off);
    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(*window);
    
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Glad crash" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    #ifdef debug
    std::cout << "glad sorted" << std::endl;
    #endif
}




/**
 * @brief Main function for Powergrid program
 * @param argc
 * @param argv
 * @return Error value
 */
int main(int argc, char **argv) {
    //Init variables
    GLFWwindow* window;
    GLuint vao, vbo;
    
    //Startup sequence
    startup(&window);
    setCallbacks(&window);
    std::vector<Program> programs = loadPrograms();
    
    #ifdef debug
    std::cout << glGetString(GL_VERSION) << " : " << GLVersion.major << GLVersion.minor << std::endl;
    #endif
    
    //Arrays:
    //You can check if arrays are generated or not using gllsVertexArray
    glGenBuffers(1, &vbo);
//    glBindBuffers(GL_ARRAY_BUFFER, VBO);
//    glBindBuffers(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    Player pc;
    GLint variant = 0;
    
    float scale_coeff = 1.f;
    
    
    WorldData world_state;
    
    std::vector<DisplayObject> objects;
    
    while(!glfwWindowShouldClose(window)) {
        //Get timestamp
        auto delta_t = world_state.get_delta_t();
        
        //Track FPS.
        auto fps = world_state.check_fps();
        if(fps) std::cout << "FPS: " << fps << std::endl;
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        
        float x_scale = scale_coeff * ((width != height) * (float) height / (float) width + (width == height));
        float y_scale = scale_coeff;
        
        const float scale[] = { 
            x_scale, 0.f, 0.f, 0.f,
            0.f, y_scale, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        };
        
        //Set changing screen color.
        float timeSin = (float)sin(glfwGetTime()) * 0.5f;
        float timeCos = (float)cos(glfwGetTime()) * 0.5f;
        const GLfloat color[] = { timeSin + 0.5f, timeCos + 0.5f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, color);
        
        GLfloat attrib[] = { 0.0f, 0.0f, 0.0f, 0.0f};
        pc.getPosition(attrib);
        
        double step_length = scale_coeff * 0.001 * delta_t / 256;
        
        int y_direction = glfwGetKey(window, GLFW_KEY_W) - glfwGetKey(window, GLFW_KEY_S);
        int x_direction = glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A);
        
        if(x_direction != 0 && y_direction != 0) step_length /= SQRT_2;
        
        attrib[1] += y_direction * step_length;
        attrib[0] += x_direction * step_length;

        pc.setPosition(attrib);
        
        attrib[1] *= scale_coeff;
        attrib[0] *= scale_coeff;
        
        double cursorPos[2];
        glfwGetCursorPos(window, cursorPos, cursorPos + 1);
        
        //Normalise because the frame treats a rectangle as a square for angles (45 degree corners).
        cursorPos[1] = (2 * (cursorPos[1] / (float) height) - 1 + attrib[1]) * x_scale;
        cursorPos[0] = (2 * (cursorPos[0] / (float) width) - 1 - attrib[0]) * y_scale;
        float radians = (float) (atan(cursorPos[1]/cursorPos[0]) + (cursorPos[0] < 0) * M_PI);
        
//        glBitmap();
        
        if(getMousebuttonFlag()) {
            variant = !variant;
            setMousebuttonFlag(0);
        }
        
        scale_coeff = (float) getScrollFlag() * 0.1f;
        
        glVertexAttrib4fv(0, attrib);
        for(auto program: programs) {
            glUseProgram(program.ID);
            
            glUniform1i(1, variant);
            glUniformMatrix4fv(2, 1, GL_FALSE, scale);
            
            glUniform1f(3, radians);
            
            glDrawArrays(program.drawType, 0, 4);
        }
        attrib[0] = -0.5f;
        attrib[1] = -0.5f;
        
        glVertexAttrib4fv(0, attrib);
        glUseProgram(programs.at(0).ID);
        glUniform1i(1, variant);
        glUniformMatrix4fv(2, 1, GL_FALSE, scale);
        
        glUniform1f(3, radians);
        
        glDrawArrays(programs.at(0).drawType, 0, 4);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //Close up shop
    glDeleteVertexArrays(1, &vao);
    for(auto program: programs) {
        glDeleteProgram(program.ID);
    }
    glDeleteVertexArrays(1, &vao);
    
    glfwTerminate();
    std::cout << "Program successfully terminated." << std::endl;
	return 0;
}