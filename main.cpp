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

//http://www-cs-students.stanford.edu/%7Eamitp/gameprog.html

//https://www.gamasutra.com/blogs/MichaelKissner/20151027/257369/Writing_a_Game_Engine_from_Scratch__Part_1_Messaging.php

//https://www.youtube.com/watch?v=Cfe3sO_L0fM&feature=share




//Working out the difference between using a VAO and using VertexAttrib/Uniforms
//https://www.reddit.com/r/opengl/comments/4e9jmw/is_it_better_to_separate_the_vbo_update_from_the/d1ydon0/

/**
 * DEBUG DEFINES
 * debug_all
 * debug_shaders
 */

/********************************************************************************
 *******                             Includes                             *******
 *******************************************************************************/
//Include this everywhere
#include "debug.h"

//Abstract functions
#include "callbacks.h"
#include "shapes.h"
#include "ShaderStore.h"
#include "player.h"
#include "WorldData.h"
#include "BasicEnemy.h"


//Includes
#include <fstream>

#define _USE_MATH_DEFINES
#include <cmath>

//My math library
#include "math.h"

#include "glad/glad.h"
#include "glfw3.h"



//Text Rendering
#define STB_TRUETYPE_IMPLEMENTATION 1
#include "stb_truetype.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
//  Abstract out the drawing and the game logic
//  Bullets shooting, object addition implemented.
//  Passing lifecycle and movement behaviour around as std::functions.

//NEXT STEP:
//  For the Menu: find out what is needed to get characters up and going. May need bitmaps.
//  Print bitmaps
//  Implement a Resource Manager
//  Implement key mapping
//  Look into how passing 3D models works. That will answers a lot of questions.
//  Get buttons working.

//  Get a menu going.

//  Engine makes the actual game take years to design. This was expected, but jesus.






void basic_enemy_movement_behaviour(WorldData& world, DisplayObject& draw_object) {
    draw_object.radians = world.getBearing2D(draw_object.location, world.display_objects.at(0).location);
    draw_object.real_location[0] += cos(draw_object.radians) * 0.01;
    draw_object.real_location[1] -= sin(draw_object.radians) * 0.01;
}

void basic_enemy_collision_detection(DisplayObject& object, DisplayObject& collider) {
    //Check if any of the four vertices are within the other 4 vertices.
}

void bullet_movement_behaviour(WorldData& world, DisplayObject& draw_object) {
    draw_object.real_location[0] += cos(draw_object.radians) * 0.1;
    draw_object.real_location[1] -= sin(draw_object.radians) * 0.1;
}

bool bullet_lifecycle_condition(DisplayObject& bullet) {
    int lifetime = duration_cast<milliseconds>(steady_clock::now() - bullet.creation_timestamp).count();
    if(lifetime > /* BULLET_LIFETIME */ 1000) {
        return true;
    }
    return false;
}

//typedef struct
//{
//   float x0,y0,s0,t0; // top-left
//   float x1,y1,s1,t1; // bottom-right
//} stbtt_aligned_quad;

//void my_stbtt_print(WorldData world, GLuint ftex, float x, float y, char *text)
//{
//    // assume orthographic projection with units = screen pixels, origin at top left
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, ftex);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    glUseProgram(world.programs(2));
//    
////    glBegin(GL_TRIANGLE_FAN);
//    while (*text) {
//        if (*text >= 32 && *text < 128) {
//            stbtt_aligned_quad q;
//            stbtt_GetBakedQuad(cdata, 512,512, *text-32, &x,&y,&q,1);//1=opengl & d3d10+,0=d3d9
//            glTexCoord2f(q.s0,q.t1); glVertex2f(q.x0,q.y0);
//            glTexCoord2f(q.s1,q.t1); glVertex2f(q.x1,q.y0);
//            glTexCoord2f(q.s1,q.t0); glVertex2f(q.x1,q.y1);
//            glTexCoord2f(q.s0,q.t0); glVertex2f(q.x0,q.y1);
//        }
//        ++text;
//    }
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 0);
////    glEnd();
//}

/**
 * @brief Main function for Powergrid program
 * @param argc
 * @param argv
 * @return Error value
 */
int main(int argc, char **argv) {
    //Init variables
    GLuint VAO, VBO, VAO1, VBO1;
    unsigned int EBO, EBO1;
    
    //Startup sequence
    WorldData world; 
    
    startup(&world.window);
    setCallbacks(&world.window);    
    world.init_window();
    
    std::vector<Program> programs = loadPrograms();
    
    #ifdef debug
    std::cout << glGetString(GL_VERSION) << " : " << GLVersion.major << GLVersion.minor << std::endl;
    #endif
    
    
    
    
    
    
    
    
    
    /**
     * LEARN OPENLGL TUTORIAL
     * 
     * Extra reading
     * https://stackoverflow.com/questions/19636054/opengl-drawarrays-or-drawelements
     */
    
    float scale = 0.7f;
    float vertices[] = {
         scale,  scale, 0.f,      0.f, 0.f,
         scale, -scale, 0.f,      0.f, 1.f,
        -scale, -scale, 0.f,      1.f, 1.f,
        -scale,  scale, 0.f,      1.f, 0.f 
    };
    
    float offset = 0.7f;
    float vertices1[] = {
        0.3f + offset,  0.3f + offset, 0.f,       0.f, 0.f,
        0.3f + offset,  0.2f + offset, 0.f,       1.f, 0.f,
        0.2f + offset,  0.2f + offset, 0.f,       1.f, 1.f,
        0.2f + offset,  0.3f + offset, 0.f,       0.f, 1.f 
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    //Arrays:
    //You can check if arrays are generated or not using gllsVertexArray
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),  (void*) (3 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(1);
    
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   TexCoord = aTexCoord;\n"
        "}\0";
        
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"
        "void main()\n"
        "{\n"
        "    FragColor = texture(ourTexture, TexCoord);\n"
        "}\0";
        
    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    int  success = 0, success1 = 0;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success1);
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glUseProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
    
    std::cout << "Success IV: " << success << "!" << std::endl;

    
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    if(!success1) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //IMPORTANT: How to set up vertex attributes.
    /*
     * In order to pass things in with a vbo, you need to tell opengl what the data looks like.
     * In this case, the position is decribes as (x, y, x), each as 4 byte (32 bit) value.
     * this means a stride of 12, but and offset of zero as there is only vertices to worry about.
     * 
     * 
     */
    //glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,    const void * pointer);
    glVertexAttribPointer(   0,            3,          GL_FLOAT,    GL_FALSE,             5 * sizeof(float), (void*) 0); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(1);
    
    
    //Apparently OpenGL Core requires a VAO to draw things, though I disagree.
    //A VAO is used to store the Vertex Attrib pointer so you don't have to recall it every time.
    //It lets you simply rebind a VAO instead of redoing a vertexattribpointer call. Cool.
    
    const float texCoords[] = {
        0.f, 0.f,
        1.f, 0.f,
        0.5f, 1.f
    };  
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    const float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../resources/textures/stock_images/binocupede.jpg", &width, &height, &nrChannels, 0); 

    if(data) {
        
    } else {
        std::cout << "Image loading gone wrong" << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    
    glUniform1i(1, 0);
    
    #ifdef main_code
    while(0) {
    #else
    while(!glfwWindowShouldClose(world.window)) {
    #endif
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glUseProgram(shaderProgram);

        //The last element buffer object tjat gets bound while a VAO is bound gets stred as that VAO's element
        //Buffer object.
        glBindVertexArray(VAO);
        
        
        //Then
//        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Or
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(world.window);
        glfwPollEvents();
    }  
    
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    


//    glBindBuffers(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
//    glCreateVertexArrays(1, &VAO);

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
    basic_enemy.movement_behaviour = basic_enemy_movement_behaviour;
    basic_enemy.real_location[0] = -0.5f;
    basic_enemy.real_location[1] = -0.5f;
    
    for(int i = 0; i < 4; i++) {
        basic_enemy.real_location[i % 2] *= -1.f;
        world.display_objects.push_back(basic_enemy);
    }
    
    
    //Font Stuff:
    unsigned char ttf_buffer[1<<20];
    unsigned char temp_bitmap[512*512];
    
    stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
    GLuint ftex;
    
    fread(ttf_buffer, 1, 1<<20, fopen("c:/windows/fonts/times.ttf", "rb"));
    stbtt_BakeFontBitmap(ttf_buffer,0, 32.0, temp_bitmap,512,512, 32,96, cdata); // no guarantee this fits!
    // can free ttf_buffer at this point
    glGenTextures(1, &ftex);
    glBindTexture(GL_TEXTURE_2D, ftex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
    // can free temp_bitmap at this point
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    #ifdef debug_all
    std::cout << "Done." << std::endl;
    #endif
    

    
    #ifdef main_code
    while(!glfwWindowShouldClose(world.window)) {
    #else
    while(0) {
    #endif
        world.calculate_timestep();
        
        //Track FPS.
        auto fps = world.check_fps();
        if(fps) std::cout << "FPS: " << fps << std::endl;
        
        //Check window, and set scale
        world.check_window();
        
        GLfloat scale[] = { world.x_scale, world.y_scale, 0.f, 0.f };
        
        //Set changing screen color.
        float timeSin = (float)sin(glfwGetTime()) * 0.5f;
        float timeCos = (float)cos(glfwGetTime()) * 0.5f;
        const GLfloat color[] = { timeSin + 0.5f, timeCos + 0.5f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, color);
        
        GLfloat attrib[] = { 0.0f, 0.0f, 0.0f, 0.0f};
        
        for(int i = 0; i < 4; i++) attrib[i] = world.display_objects.at(0).real_location[i];
//        for(int i = 0; i < 4; i++) attrib[i] = world.display_objects.at(1).real_location[i];
        
        double step_length = scale_coeff * 0.000002 * world.get_delta_t();
        
        int y_direction = glfwGetKey(world.window, GLFW_KEY_W) - glfwGetKey(world.window, GLFW_KEY_S);
        int x_direction = glfwGetKey(world.window, GLFW_KEY_D) - glfwGetKey(world.window, GLFW_KEY_A);
        
        if(x_direction != 0 && y_direction != 0) step_length /= SQRT_2;
        
        attrib[1] += y_direction * step_length;
        attrib[0] += x_direction * step_length;
        
        //Set absolute position
        world.display_objects.at(0).setLocation(attrib, scale);
        world.display_objects.at(1).setLocation(attrib, scale);
        
        world.display_objects.at(0).radians = world.getBearingToCursor(world.display_objects.at(0).location);
        world.display_objects.at(1).radians = world.display_objects.at(0).radians;
        

        for(int i = world.display_objects.size() - 1; i >= 2; i--) {
            DisplayObject& target = world.display_objects.at(i);
            target.movement_behaviour(world, target);
            target.setLocation(target.real_location, scale);
            
            if(target.lifecycle_conditions && target.lifecycle_conditions(world.display_objects.at(i))) {
                world.display_objects.erase(world.display_objects.begin() + i);
            }
        }
            
        if(getLeftClickFlag()) {
            DisplayObject bullet;
            bullet.program = programs.at(0);
            bullet.movement_behaviour = bullet_movement_behaviour;
            bullet.lifecycle_conditions = bullet_lifecycle_condition;
            
            bullet.radians = world.display_objects.at(0).radians;
            bullet.real_location[0] = world.display_objects.at(0).real_location[0];
            bullet.real_location[1] = world.display_objects.at(0).real_location[1];
            world.display_objects.push_back(bullet);
            
            for(int i = 0; i < 100; i++) {
            basic_enemy.real_location[0] = ((float)rand()/(float)(RAND_MAX)) * 2 - 1;
            basic_enemy.real_location[1] = ((float)rand()/(float)(RAND_MAX)) * 2 - 1;
            
            world.display_objects.push_back(basic_enemy);
            }
            resetLeftClickFlag();
            std::cout << "Enemies: " << world.display_objects.size() - 2 << std::endl;
        }
        if(getRightClickFlag()) {
            if(world.display_objects.size() > 2) {
                world.display_objects.pop_back();
            }
            resetRightClickFlag();
        }
        
        world.scale_factor = (float) getScrollFlag() * 0.1f;
        
        //Attribs can be set just once
        //Uniforms need to be reset when the program changes.
        
        //Need to move data into objects.
        glVertexAttrib4fv(0, scale);
            
        world.draw_objects();
        
        glfwSwapBuffers(world.window);
        glfwPollEvents();
    }
    
    //Close up shop
    glDeleteVertexArrays(1, &VAO);
    for(auto program: programs) {
        glDeleteProgram(program.ID);
    }
    glDeleteVertexArrays(1, &VAO);
    
    glfwTerminate();
    std::cout << "Program successfully terminated." << std::endl;
	return 0;
}









void startup(GLFWwindow** window) {
    
    srand(time(NULL));
    resetLeftClickFlag();
    resetRightClickFlag();
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