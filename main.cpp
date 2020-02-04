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

#include "main.h"

//https://thebookofshaders.com/07/



#define DEV

#define SHADER_PATH         "..\\resources\\shaders\\"
#define SHADER_INDEX_FILE   "..\\resources\\shaders\\index.txt"

#define debug1


//NEXT STEP:
//Move using WASD, shoot something, and get a menu going.
//For the Menu: find out what is needed to get characters up and going. May need bitmaps.


namespace Frame {
    int width  {1280};
    int height  {960};
    int x_off   {100};
    int y_off     {0};
    const char* title = "PowerGrid";
}

//Global variables
ShaderStore shaderStore;

/**
 * @brief 
 * @param frame
 */
void setCallbacks(GLFWwindow** frame) {
    GLFWwindow* window = *frame;
    
    glfwMakeContextCurrent(window);
    glfwSetWindowFocusCallback(window, close_on_unfocus);
    glfwSetMouseButtonCallback(window, mousebutton_flag_callback);
    glfwSetKeyCallback(window, general_keyboard_callback);
}


//static GLuint create_buffer(GLenum target, const void* data, GLsizei buffer_size) {
//    GLuint buffer;
//    glGenBuffer(1, &buffer);
//    glBindBuffer(target, buffer);
//    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
//    return buffer;
//}

void loadShaders() {
    std::string line, path, index(SHADER_INDEX_FILE);
    std::ifstream shaderIndex;
    shaderIndex.open(index);
    
    //Debug information to confirm the shaders have loaded correctly.
    #ifdef debug
    if(shaderIndex) {
        std::cout << "Shader index opened: " <<index.c_str() << std::endl;
    } else {
        std::cout << "Shader index failed: " << index.c_str() << std::endl;
    }
    #endif
    
    /* Iterate over the index file. The first characters determines the shader
     * type, the second character is a semicolon and the rest of the line is 
     * the files address.
     */
    while(std::getline(shaderIndex, line)) {
        std::cout << "Line in: " << line << std::endl;
        
        path.assign(SHADER_PATH).append(line.substr(2));
        char shaderType = line.at(0);
        switch(shaderType) {
            case 'v':
                shaderStore.addShader(path, GL_VERTEX_SHADER);
                break;
            case 'f':
                shaderStore.addShader(path, GL_FRAGMENT_SHADER);
                break;
            case '/':
                break;
            #ifdef debug
            default:
                std::cout << "ShaderType not recognised: " << shaderType << std::endl;
            #endif
        }
    }
}


void startup(GLFWwindow** window) {
    
    srand(time(NULL));
    setMousebuttonFlag(0);
    
    if (!glfwInit()) exit(EXIT_FAILURE);
    
    #ifdef debug
    std::cout << "glfw init successful" << std::endl;
    #endif
    
    glfwSetErrorCallback(basic_error_callback);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    
    #ifdef debug
    std::cout << getch();
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

int main(int argc, char **argv) {
    //Init variables
    GLFWwindow* window;
    GLuint program, vao, vbo;
    
    //Startup sequence
    startup(&window);
    setCallbacks(&window);
    
    #ifdef debug
    std::cout << glGetString(GL_VERSION) << " : " << GLVersion.major << GLVersion.minor << std::endl;
    #endif
    
    /* Create program, attach shaders to it, and link it.
     * Shaders are accessed from the \resources\shaders folder.
     * Shaders are stored in the a ShaderStore class.
     */
    program = glCreateProgram();
    loadShaders();
    
    shaderStore.attachAll(program);
    glLinkProgram(program);
    
    // Delete the shaders as the program has them now
    shaderStore.deleteAll();
    
//    glGenBuffers(1, &vbo);
//    glBindBuffers(GL_ARRAY_BUFFER, VBO);
//    glBindBuffers(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    Player pc;
    
//    pc.setPosition();
    
    while(!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        //Sets the viewport, first 2 car's specify the bottom right hand corner
        glViewport(0, 0, width, height);
        glClearColor(0.f, 0.f, 1.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Draw here
        
        const GLfloat color[] = { (float)sin(glfwGetTime()) * 0.5f + 0.5f, 
                (float)cos(glfwGetTime()) * 0.5f + 0.5f, 0.0f, 1.0f
        };
        glClearBufferfv(GL_COLOR, 0, color);
        
        
        GLfloat attrib[] = { (float)sin(glfwGetTime()) * 0.5f, 
                (float)cos(glfwGetTime()) * 0.6f, 0.0f, 0.0f
        };
        
        glUseProgram(program);
        
        float pcPos[2];
        double cursorPos[2];
        
        pc.getPosition(pcPos);
        glfwGetCursorPos(window, cursorPos, cursorPos + 1);
        cursorPos[1] += pcPos[1] - (float) height/2;
        cursorPos[0] += pcPos[0] - (float) width/2;
        if(cursorPos[0] > 0) {
            cursorPos[0] += tan(1.05 * M_PI/12) * abs(cursorPos[1]);
        } else {
            cursorPos[0] -= tan(1.05 * M_PI/12) * abs(cursorPos[1]);
        }
        
        double radians = tanh(cursorPos[1]/(cursorPos[0])) * (M_PI_2);
        if(cursorPos[0] < 0) radians += M_PI;
        
        std::cout << cursorPos[0] << " " << cursorPos[1] << " " << radians << std::endl;
        
        const float rotate[] = { 
            (float) cos(radians), (float) sin(radians), 0.f, 0.f,
            (float) -sin(radians), (float) cos(radians), 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        };
        
        glUniformMatrix4fv(1, 1, GL_TRUE, rotate);
        
        glVertexAttrib4fv(0, attrib);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    //Close up shop
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vao);
    
    glfwTerminate();
	return 0;
}