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

//https://www.haroldserrano.com/articles

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


//Initial setup for window.
#define WINDOW_TITLE "PowerGrid"
#define INITIAL_WIDTH 960
#define INITIAL_HEIGHT INITIAL_WIDTH
#define INITIAL_X_OFF 800
#define INITIAL_Y_OFF 50


/********************************************************************************
 *******                           Prototypes                             *******
 *******************************************************************************/
void startup(GLFWwindow** window);






//GOALS ACHIEVED:
//  Square drawn and rotating with mouse
//  Movement with WASD

//NEXT STEP:
//For the Menu: find out what is needed to get characters up and going. May need bitmaps.
//Print bitmaps
//Abstract out the drawing and the game logic

//Implement a Resource Manager
//Implement key mapping


//Shoot something, and get a menu going.
//  - New transient class added
//  - Need to work out how to throw around behaviour for different objects. Function pointers seems probably.
//  - Engine makes the actual game take years to design. This was expected, but jesus.



//static GLuint create_buffer(GLenum target, const void* data, GLsizei buffer_size) {
//    GLuint buffer;
//    glGenBuffer(1, &buffer);
//    glBindBuffer(target, buffer);
//    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
//    return buffer;
//}







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
    
    
    WorldData world;
    
    //Startup sequence
    startup(&world.window);
    setCallbacks(&world.window);    

    world.init_window();
    
        
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
    
    std::cout << "Creating objects: " << programs.size() << std::endl;
    DisplayObject pcObject, pcLine;
    pcObject.program = programs.at(0);
    pcLine.program   = programs.at(1);
    world.display_objects.push_back(pcObject);
    world.display_objects.push_back(pcLine);
    
    DisplayObject basic_enemy;
    basic_enemy.program = programs.at(0);
    world.display_objects.push_back(basic_enemy);
    std::cout << "Done." << std::endl;
    
    while(!glfwWindowShouldClose(world.window)) {
        //Get timestamp
        auto delta_t = world.get_delta_t();
        
        //Track FPS.
        auto fps = world.check_fps();
        if(fps) std::cout << "FPS: " << fps << std::endl;
        
        //Check window, and set scale
        world.check_window();
        
        const float scale[] = { 
            world.x_scale, 0.f, 0.f, 0.f,
            0.f, world.y_scale, 0.f, 0.f,
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
        
        int y_direction = glfwGetKey(world.window, GLFW_KEY_W) - glfwGetKey(world.window, GLFW_KEY_S);
        int x_direction = glfwGetKey(world.window, GLFW_KEY_D) - glfwGetKey(world.window, GLFW_KEY_A);
        
        if(x_direction != 0 && y_direction != 0) step_length /= SQRT_2;
        
        attrib[1] += y_direction * step_length;
        attrib[0] += x_direction * step_length;

        //Set absolute position
        pc.setPosition(attrib);
        
        //Scale value.
        attrib[1] *= scale_coeff;
        attrib[0] *= scale_coeff;
        
        //Get cursor position.
        glfwGetCursorPos(world.window, world.cursor_position, world.cursor_position + 1);
        
        //Normalise because the frame treats a rectangle as a square for angles (45 degree corners).
        world.cursor_position[1] = (2 * (world.cursor_position[1] / (float) world.height) - 1 + attrib[1]) * world.x_scale;
        world.cursor_position[0] = (2 * (world.cursor_position[0] / (float) world.width) - 1 - attrib[0]) * world.y_scale;
        float radians = (float) (atan(
            world.cursor_position[1]/world.cursor_position[0]) + 
            (world.cursor_position[0] < 0) * M_PI
        );
        
        
//        glBitmap();
        
        if(getMousebuttonFlag()) {
            variant = !variant;
            setMousebuttonFlag(0);
        }
        
        scale_coeff = (float) getScrollFlag() * 0.1f;
        
        glVertexAttrib4fv(0, attrib);
        for(auto draw_object: world.display_objects) {
            
            glUseProgram(draw_object.program.ID);
            
            glUniform1i(1, variant);
            glUniformMatrix4fv(2, 1, GL_FALSE, scale);
            
            glUniform1f(3, radians);
            
            glDrawArrays(draw_object.program.drawType, 0, 4);
        }
        attrib[0] = -0.5f;
        attrib[1] = -0.5f;
        
        glVertexAttrib4fv(0, attrib);
        glUseProgram(programs.at(0).ID);
        glUniform1i(1, variant);
        glUniformMatrix4fv(2, 1, GL_FALSE, scale);
        
        glUniform1f(3, radians);
        
        glDrawArrays(programs.at(0).drawType, 0, 4);
        
        
        glfwSwapBuffers(world.window);
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
        INITIAL_WIDTH,
        INITIAL_HEIGHT,
        WINDOW_TITLE,
        NULL, //glfwGetPrimaryMonitor(), //<- does fullscreen
        NULL
    );
    
    glfwSetWindowPos(*window, INITIAL_X_OFF, INITIAL_Y_OFF);
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