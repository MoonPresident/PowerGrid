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



#define DEV

#define ARRAY_2D 2
#define ARRAY_COLOR 3

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


//static GLuint create_buffer(GLenum target, const void* data, GLsizei buffer_size) {
//    GLuint buffer;
//    glGenBuffer(1, &buffer);
//    glBindBuffer(target, buffer);
//    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
//    return buffer;
//}


void startup(GLFWwindow** window);

int main(int argc, char **argv) {
    //Init variables
    GLFWwindow* window;
    GLuint vertex_shader, fragment_shader, program, vao, vbo;
    //Startup sequence
    srand(time(NULL));
    setMousebuttonFlag(0);
    startup(&window);
    setCallbacks(&window);
    
    std::cout << glGetString(GL_VERSION) << " : " << GLVersion.major << GLVersion.minor << std::endl;
    
    static const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f,
    };
    static const GLushort elements[] = { 0, 1, 2, 3 };
    


    
    std::ofstream extension_file;
    extension_file.open("gl_extensions.txt");
    extension_file << glGetString(GL_EXTENSIONS);
    extension_file.close();
    
    
    // Create and compile vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    
    // Create and compile fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    
    glPointSize(40.0f);
    
    // Create program, attach shaders to it, and link it
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    // Delete the shaders as the program has them now
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
//    glGenBuffers(1, &vbo);
//    glBindBuffers(GL_ARRAY_BUFFER, VBO);
//    glBindBuffers(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);


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
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
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



void startup(GLFWwindow** window) {
    
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
