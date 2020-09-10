/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * 
 * 
 * Needs links included to opengl32 and gdi32
 * Get GLM installed. Or make your own vector math, up to you.
 */
 
 //https://www.glprogramming.com/red/chapter02.html
 //https://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/opengl_programming.html

//Abstract functions
#include "callbacks.h"
#include "shapes.h"
#include "ShaderStore.h"
#include "player.h"

//Includes
#include <fstream>
#include "time.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "glad/glad.h"
#include "glfw3.h"




//https://thebookofshaders.com/07/
#define SHADER_PATH         "..\\resources\\shaders\\"
#define SHADER_INDEX_FILE   "..\\resources\\shaders\\index.txt"

#define debug1

//GOALS ACHIEVED:
//  Square drawn and rotating with mouse
//  Movement with WASD

//NEXT STEP:
//Shoot something, and get a menu going.
//For the Menu: find out what is needed to get characters up and going. May need bitmaps.


namespace Frame {
    int width  {960};//1280};
    int height  {960};
    int x_off   {100};
    int y_off     {0};
    const char* title = "PowerGrid";
}

//Global variables
ShaderStore shaderStore;


//static GLuint create_buffer(GLenum target, const void* data, GLsizei buffer_size) {
//    GLuint buffer;
//    glGenBuffer(1, &buffer);
//    glBindBuffer(target, buffer);
//    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
//    return buffer;
//}

std::vector<Program> loadPrograms() {
    std::vector<Program> programs;
    std::string line, path, index(SHADER_INDEX_FILE);
    std::ifstream shaderIndex;
    shaderIndex.open(index);
    
    //Debug information to confirm the shaders have loaded correctly.
    #ifdef debug
    cout << (shaderIndex ? "Shader opened: " : "Shader failed: ") << index.c_str() << endl;
    #endif
    
    /* Iterate over the index file. The first characters determines the shader
     * type, the second character is a semicolon and the rest of the line is 
     * the files address.
     */
     
    while(getline(shaderIndex, line)) {
        #ifdef debug
        std::cout << "Line in: " << line << std::endl;
        #endif
        std::cout << programs.size() << std::endl;
        path.assign(SHADER_PATH).append(line.substr(2));
        char shaderType = line.at(0);
        switch(shaderType) {
            case 'p': {
                Program program;
                program.ID = glCreateProgram();
                program.drawType = (line.at(1) == 'l') * GL_LINES + (line.at(1) == 'f') * GL_TRIANGLE_FAN;
                programs.push_back(program);
                break;
            }
            case 'v':
                programs.back().shaderStore.addShader(path, GL_VERTEX_SHADER);
                break;
            case 'f':
                programs.back().shaderStore.addShader(path, GL_FRAGMENT_SHADER);
            case '/':
                break;
            
            #ifdef debug

            default:
                cout << "ShaderType not recognised: " << shaderType << endl;
            #endif
        }
    }
    
    //Compile the shader programs, 1 program at a time
    for(auto program: programs) {
        program.shaderStore.attachAll(program.ID);
        glLinkProgram(program.ID);
        program.shaderStore.deleteAll();
    }
    return programs;
}


void startup(GLFWwindow** window) {
    
    srand(time(NULL));
    setMousebuttonFlag(0);
    
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
    
    #ifdef debug
    cout << getch();
    #endif
    
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
    
    glfwMakeContextCurrent(*window);
    
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Glad crash" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    #ifdef debug
    std::cout << "glad sorted" << std::endl;
    #endif

}


void handleViewport(int *width, int *height, float *aspect_ratio) {
    
}


/**
 * @brief Main function for Powergrid program
 * @param argc
 * @param argv
 * @return Error value
 */
int main(int argc, char **argv) {
    //Init variables
    Player pc;
    GLFWwindow* window;
    GLuint vao, vbo;
    
    float pcInit[] = { 0.0f, 0.0f};
    GLint variant = 0;
    pc.setPosition(pcInit);
    
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
    
    while(!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        
        //Set changing screen volor.
        float timeSin = (float)sin(glfwGetTime()) * 0.5f;
        float timeCos = (float)cos(glfwGetTime()) * 0.5f;
        const GLfloat color[] = { timeSin + 0.5f, timeCos + 0.5f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, color);
        
        GLfloat attrib[] = { 0.0f, 0.0f, 0.0f, 0.0f};
        float pcPos[2];
        pc.getPosition(pcPos);
        
        double step_length = 0.002;
        pcPos[1] += glfwGetKey(window, GLFW_KEY_W) * step_length - glfwGetKey(window, GLFW_KEY_S) * step_length;
        pcPos[0] += glfwGetKey(window, GLFW_KEY_D) * step_length - glfwGetKey(window, GLFW_KEY_A) * step_length;
        
        pc.setPosition(pcPos);
//        cout << pcPos[0] << " " << pcPos[1] << endl;
        
        attrib[0] = pcPos[0];
        attrib[1] = pcPos[1];
        
        double cursorPos[2];
        glfwGetCursorPos(window, cursorPos, cursorPos + 1);
        
        //Normalise because the frame treats a rectangle as a square for angles (45 degree corners).
        cursorPos[1] = 2 * (cursorPos[1] / (float) height) - 1 + pcPos[1];
        cursorPos[0] = 2 * (cursorPos[0] / (float) width) - 1 - pcPos[0];
//        cout << cursorPos[0] << " " << cursorPos[1] << " " << pcPos[0] << " " << pcPos[1] << endl;
        double radians = atan(cursorPos[1]/cursorPos[0]) + (cursorPos[0] < 0) * M_PI;

        float cosMag = static_cast<float>(cos(radians));
        float sinMag = static_cast<float>(sin(radians));
        const float rotate[] = { 
            cosMag, -sinMag, 0.f, 0.f,
            sinMag, cosMag, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        };
        
        
        float x_scale = (width < height) * (float) height / (float) width + (width > height) * (1 - (float) height / (float) width);
        float y_scale = 1.f;
        
        std::cout << "Scale: " << x_scale << " ";
        
        const float scale[] = { 
            x_scale, 0.f, 0.f, 0.f,
            0.f, y_scale, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        };
        
        if(getMousebuttonFlag()) {
            variant = !variant;
            setMousebuttonFlag(0);
        }
        
        glLineWidth(5.0f + timeSin * 6.0f);
        
        float f_vec[] = {(float) width, (float) height};
        
        std::cout << f_vec[0] << " " << f_vec[1] << std::endl;
        glVertexAttrib4fv(0, attrib);
        for(auto program: programs) {
            glUseProgram(program.ID);
            
            glUniformMatrix4fv(1, 1, GL_FALSE, rotate);
            glUniform1i(2, variant);
            glUniformMatrix4fv(3, 1, GL_FALSE, scale);
            
            glDrawArrays(program.drawType, 0, 4);
        }
        
        glfwPollEvents();
        glfwSwapBuffers(window);
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