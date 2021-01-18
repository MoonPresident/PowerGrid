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

//https://teaching.csse.uwa.edu.au/units/CITS3003/lectures/04-OpenGL-Example-Program.pdf




/**
 * THIS!!! https://docs.gl/gl4/glBufferData
**/


/********************************************************************************
 *******                             Includes                             *******
 *******************************************************************************/
//Include this everywhere
#include "my_debug.h"

//Abstract functions
#include "callbacks.h"
#include "shapes.h"
#include "ShaderStore.h"
#include "WorldData.h"
#include "Terminal.h"
#include "Font.h"
#include "Camera.h"


//Includes
#include <fstream>
#include <utility>
#include <vector>
#include <numeric>

#define _USE_MATH_DEFINES
#include <cmath>

//My math library
#include "math.h"

#include "glad/glad.h"
#include "glfw3.h"

//GLM library
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"



//Text Rendering
//#define STB_TRUETYPE_IMPLEMENTATION 1
//#include "stb_truetype.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Freetype kinda sucks to get working
//https://www.gregwessels.com/dev/2017/05/02/freetype-harfbuzz.html
//Idk tho
/********************************************************************************
 *******                           Namespaces                             *******
********************************************************************************/
using namespace std::chrono;

/********************************************************************************
 *******                             Defines                              *******
********************************************************************************/

/**
 * DEBUG DEFINES
 * debug_all
 * debug_shaders
**/



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
*******                              Startup                              *******
********************************************************************************/

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
        std::cout << "Glad crashed. Exiting." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    #ifdef debug
    std::cout << "Glad loaded." << std::endl;
    #endif
}






//GOALS ACHIEVED:
//  Square drawn and rotating with mouse
//  Movement with WASD
//  Abstract out the drawing and the game logic
//  Bullets shooting, object addition implemented.
//  Passing lifecycle and movement behaviour around as std::functions.
//  Print Character Bitmaps

//NEXT STEP:
//  Implement a Resource Manager
//  Implement key mapping
//  Look into how passing 3D models works. That will answers a lot of questions.
//  Get buttons working.

//  Get a menu going.

//  Engine makes the actual game take years to design. This was expected, but jesus.
//  Get Terminal Working
//  Get an input interface
//  Work out model for state machine






//void basic_enemy_movement_behaviour(WorldData& world, DisplayObject& draw_object) {
//    draw_object.radians = world.getBearing2D(draw_object.location, world.display_objects.at(0).location);
//    draw_object.real_location[0] += cos(draw_object.radians) * 0.01;
//    draw_object.real_location[1] -= sin(draw_object.radians) * 0.01;
//}
//
//void basic_enemy_collision_detection(DisplayObject& object, DisplayObject& collider) {
//    //Check if any of the four vertices are within the other 4 vertices.
//}
//
//void bullet_movement_behaviour(WorldData& world, DisplayObject& draw_object) {
//    draw_object.real_location[0] += cos(draw_object.radians) * 0.1;
//    draw_object.real_location[1] -= sin(draw_object.radians) * 0.1;
//}
//
//bool bullet_lifecycle_condition(DisplayObject& bullet) {
//    int lifetime = duration_cast<milliseconds>(steady_clock::now() - bullet.creation_timestamp).count();
//    if(lifetime > /* BULLET_LIFETIME */ 1000) {
//        return true;
//    }
//    return false;
//}

#define debug_getSquare
void getSquare(float square[], float width, int stride, int z_const = 0.f) {
    float half_width = width / 2;
    for(int i = 0; i < 4; i++) {
        square[stride * i    ] = half_width * ((i < 2) - (i >= 2));
        square[stride * i + 1] = half_width * (2 * (i % 2) - 1);
        square[stride * i + 2] = z_const;
    }
}

//#define debug_getCube
void getCube(float square[], float width, int stride) {
    float half_width = width / 2;
    for(int i = 0; i < 8; i++) {
        square[stride * i    ] = half_width * ((i < 4) - (i >= 4));
        square[stride * i + 1] = half_width * ((i % 4 < 2) - (i % 4 >= 2));
        square[stride * i + 2] = half_width * (2 * (i % 2) - 1);
    }
}

//#define debug_setVertexPointerFloat
void setVertexPointerFloat(std::vector<int> dataLayout) {
    //IMPORTANT: How to set up vertex attributes.
    /*
     * In order to pass things in with a vbo, you need to tell opengl what the data looks like.
     * In this case, the position is decribes as (x, y, x), each as 4 byte (32 bit) value.
     * this means a stride of 12, but and offset of zero as there is only vertices to worry about.
     * 
     * glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,    const void * pointer);
     */
    
    //Get total size, initialise offset variable and precalculate size in bytes for repeated use.
    int stride = std::accumulate(dataLayout.begin(), dataLayout.end(), 0);
    int offset = 0;
    int size = stride * sizeof(float);
    
    #ifdef debug_setVertexPointerFloat
    std::cout << "Stride: " << stride << std::endl;
    #endif
    
    //Loop
    for(int i = 0; i < dataLayout.size(); i++) {
        int step = dataLayout.at(i);
        
        #ifdef debug_setVertexPointerFloat
        std::cout << "Offset: " << offset << std::endl;
        std::cout << "Step: " << step << std::endl;
        #endif
        
        glVertexAttribPointer(i, step, GL_FLOAT, GL_FALSE, size, (void*) (offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += step;
    }
    
    #ifdef debug_setVertexPointerFloat
    std::cout << "Final Offset: " << offset << std::endl;
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
    GLuint VAO, VBO, VAO1, VBO1, EBO, EBO1;
    float moveSpeed = 5.f;
    float jumpVelocity = 2.8f;
    
    //Startup sequence
    WorldData world; 
    Camera camera;
    startup(&world.window);
    setCallbacks(&world.window);
    setMouseOffsetX(0.f);
    setMouseOffsetY(0.f);
    setMouseLastY(world.height / 2.f);
    world.init_window();
    
    std::vector<Program> programs = loadPrograms();
    
    #ifdef debug
    std::cout << glGetString(GL_VERSION) << " : " << GLVersion.major << GLVersion.minor << std::endl;
    #endif
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    Font times("c:/windows/fonts/times.ttf");
    
    float textVertices[] = {
        0.f,   0.f,   0.f,    times.q.s0, times.q.t1,
        0.f,   0.05f, 0.f,    times.q.s0, times.q.t0,
        0.05f, 0.f,   0.f,    times.q.s1, times.q.t1,
        0.05f, 0.05f, 0.f,    times.q.s1, times.q.t0,
    };
    unsigned int textIndices[] = { 0, 1, 2,     1, 2, 3, };
    
    GLuint textVAO, textVBO;
    unsigned int textEBO;
    glGenVertexArrays(1, &textVAO);
    glBindVertexArray(textVAO);
    
    glGenBuffers(1, &textVBO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textVertices), textVertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &textEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textIndices), textIndices, GL_STATIC_DRAW);
    
    std::vector<int> layout = {3, 2};
    setVertexPointerFloat(layout);
    
    
    
    #ifndef main_code
    
    /**
     * LEARN OPENLGL TUTORIAL
     * 
     * Extra reading
     * https://stackoverflow.com/questions/19636054/opengl-drawarrays-or-drawelements
     * 
     * Projection matrix notes:
     * https://www.songho.ca/opengl/gl_projectionmatrix.html
     * https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process
    **/
    
    float scale = 0.7f;
    float rot = 0.1f;
    float vertices[] = {
        0.f, 0.f, 0.f,      1.f, 1.f, rot,
        0.f, 0.f, 0.f,      1.f, 0.f, rot,
        0.f, 0.f, 0.f,      0.f, 1.f, rot,
        0.f, 0.f, 0.f,      0.f, 0.f, rot,
        0.f, 0.f, 0.f,      1.f, 1.f, rot,
        0.f, 0.f, 0.f,      1.f, 0.f, rot,
        0.f, 0.f, 0.f,      0.f, 1.f, rot,
        0.f, 0.f, 0.f,      0.f, 0.f, rot,
    };
    getCube(vertices, scale, 6);
    
    float offset = 0.7f;
    float vertices1[] = {
        0.3f + offset,  0.3f + offset, 0.f,       0.f, 0.f, rot,
        0.3f + offset,  0.2f + offset, 0.f,       1.f, 0.f, rot,
        0.2f + offset,  0.2f + offset, 0.f,       1.f, 1.f, rot,
        0.2f + offset,  0.3f + offset, 0.f,       0.f, 1.f, rot,
    };
    unsigned int indices[] = { 
        0, 1, 2,    1, 2, 3,    4, 5, 6,    5, 6, 7,
        0, 1, 4,    1, 4, 5,    2, 3, 6,    3, 6, 7,
        0, 2, 4,    2, 4, 6,    1, 3, 5,    3, 5, 7
    };
    
    //Arrays:
    //You can check if arrays are generated or not using gllsVertexArray
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), 0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    {
        std::vector<int> vboLayout = {3, 2, 1};
        setVertexPointerFloat(vboLayout);
    }
    
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    {
        std::vector<int> vboLayout = {3, 2, 1};
        setVertexPointerFloat(vboLayout);
    }
    
    
    //Apparently OpenGL Core requires a VAO to draw things, though I disagree.
    //A VAO is used to store the Vertex Attrib pointer so you don't have to recall it every time.
    //It lets you simply rebind a VAO instead of redoing a vertexattribpointer call. Cool.
    
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
    
    
    float yaw = -90.f;
    float pitch = 0.f;
    
    glm::vec3 force_vector(0.f, 0.f, 0.f); //x, y, z
    float pc_z_pos = 0.f;
    while(!glfwWindowShouldClose(world.window)) {
        //Trigger new timestep
        world.calculate_timestep();
        
        float delta_t = world.get_delta_t()  / 1000000.f;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        world.scale_factor = (float) getScrollFlag() * 0.1f;
        

        
        //Track FPS.
        auto fps = world.check_fps();
        //Things to be done once a second.
//        if(fps) {
//            std::cout << "FPS: " << fps << std::endl;
//            std::cout << "\t" << cameraPos.x << "\t" << cameraPos.y << "\t" << cameraPos.z <<
//                    "\t" << force_vector[2] << std::endl;
//        }
        float newYaw    = world.getMouseYaw() - getMouseOffsetX() * world.sensitivity;
        float newPitch  = world.getMousePitch() + getMouseOffsetY() * world.sensitivity;
        if(newPitch < -89.0f) newPitch = -89.f;
        else if (newPitch > 89.0f) newPitch = 89.f;
        world.setMouseYaw(newYaw);
        world.setMousePitch(newPitch);
        setMouseOffsetX(0.f);
        setMouseOffsetY(0.f);
        
        
        glm::vec3 direction;
        direction.x = cos(glm::radians(world.mouseYaw)) * cos(glm::radians(world.mousePitch));
        direction.y = sin(glm::radians(world.mousePitch));
        direction.z = sin(glm::radians(world.mouseYaw)) * cos(glm::radians(world.mousePitch));
        camera.cameraFront = glm::normalize(direction);

        world.check_window();
        
        glBindTexture(GL_TEXTURE_2D, texture);
//        glBindTexture(GL_TEXTURE_2D, ftex);        
        const float cameraSpeed = moveSpeed * delta_t; // adjust accordingly
        if (glfwGetKey(world.window, GLFW_KEY_W) == GLFW_PRESS)
            camera.cameraPos += cameraSpeed * glm::vec3(camera.cameraFront.x, 0.f, camera.cameraFront.z);
        if (glfwGetKey(world.window, GLFW_KEY_S) == GLFW_PRESS)
            camera.cameraPos -= cameraSpeed * glm::vec3(camera.cameraFront.x, 0.f, camera.cameraFront.z);
        if (glfwGetKey(world.window, GLFW_KEY_A) == GLFW_PRESS)
            camera.cameraPos -= glm::normalize(glm::cross( glm::vec3(camera.cameraFront.x, 0.f, camera.cameraFront.z), camera.cameraUp)) * cameraSpeed;
        if (glfwGetKey(world.window, GLFW_KEY_D) == GLFW_PRESS)
            camera.cameraPos += glm::normalize(glm::cross( glm::vec3(camera.cameraFront.x, 0.f, camera.cameraFront.z), camera.cameraUp)) * cameraSpeed;
        if(glfwGetKey(world.window, GLFW_KEY_SPACE) && force_vector.z == 0.f) {
            force_vector.z = jumpVelocity;//m/s
        }
        camera.cameraPos = glm::vec3(camera.cameraPos.x, pc_z_pos, camera.cameraPos.z);
        
        force_vector.z -= 9.8f * delta_t;
        pc_z_pos += force_vector.z * delta_t;
        if(pc_z_pos < 0.f) {
            pc_z_pos = 0.f;
            force_vector.z = 0.f;
        }
        
        camera.view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
        
        glUseProgram(programs.back().ID);
        
//        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.01f), glm::vec3(0.5f, 1.0f, 0.f));
        int modelLoc = glGetUniformLocation(programs.back().ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.model));
        
        int viewLoc = glGetUniformLocation(programs.back().ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));

        int projectionLoc = glGetUniformLocation(programs.back().ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projection));

        //The last element buffer object that gets bound while a VAO is bound gets stred as that VAO's element
        //Buffer object.
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);

        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        glBindTexture(GL_TEXTURE_2D, times.ftex);
        glUseProgram(programs.at(programs.size() - 2).ID);
        
        glBindVertexArray(textVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(world.window);
        glfwPollEvents();
    }  
    
    //Close up shop
    for(auto program: programs) {
        glDeleteProgram(program.ID);
    }
    
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    glfwTerminate();
    std::cout << "Program successfully terminated." << std::endl;
	return 0;
    
    #endif
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /**
     * MY CODE
    **/
//    GLint variant = 0;
//    float scale_coeff = 1.f;
//    
//    std::cout << "Programs: " << programs.size() << std::endl;
//    DisplayObject pcObject, pcLine;
//    pcObject.program = programs.at(0);
//    pcLine.program   = programs.at(1);
//    world.display_objects.push_back(pcObject);
    
//    world.display_objects.push_back(pcLine);
    
//    DisplayObject basic_enemy;
//    basic_enemy.program = programs.at(0);
//    basic_enemy.movement_behaviour = basic_enemy_movement_behaviour;
//    basic_enemy.real_location[0] = -0.5f;
//    basic_enemy.real_location[1] = -0.5f;
//    basic_enemy.real_location[2] = 1.f;
//    basic_enemy.real_location[3] = 1.f;
    
//    for(int i = 0; i < 4; i++) {
//        basic_enemy.real_location[i % 2] *= -1.f;
//        world.display_objects.push_back(basic_enemy);
//    }
    
//    world.initBuffers();
//        world.calculate_timestep();
//        
        //Track FPS.
//        auto fps = world.check_fps();
//        if(fps) std::cout << "FPS: " << fps << std::endl;
        
        //Check window, and set scale
//        world.check_window();
//        
//        GLfloat scale[] = { world.x_scale, world.y_scale, 0.f, 0.f };
//        
//        //Set changing screen color.
//        float timeSin = (float)sin(glfwGetTime()) * 0.5f;
//        float timeCos = (float)cos(glfwGetTime()) * 0.5f;
//        const GLfloat color[] = { timeSin + 0.5f, timeCos + 0.5f, 0.0f, 1.0f};
//        glClearBufferfv(GL_COLOR, 0, color);
//        
//        GLfloat attrib[] = { 0.0f, 0.0f, 0.0f, 0.0f};
        
//        for(int i = 0; i < 4; i++) attrib[i] = world.display_objects.at(0).real_location[i];
//        for(int i = 0; i < 4; i++) attrib[i] = world.display_objects.at(1).real_location[i];
        
//        double step_length = scale_coeff * 0.000002 * world.get_delta_t();
//        
//        int y_direction = glfwGetKey(world.window, GLFW_KEY_W) - glfwGetKey(world.window, GLFW_KEY_S);
//        int x_direction = glfwGetKey(world.window, GLFW_KEY_D) - glfwGetKey(world.window, GLFW_KEY_A);
//        
//        if(x_direction != 0 && y_direction != 0) step_length /= SQRT_2;
//        
//        attrib[1] += y_direction * step_length;
//        attrib[0] += x_direction * step_length;
//        
//        //Set absolute position
//        world.display_objects.at(0).setLocation(attrib, scale);
//        world.display_objects.at(1).setLocation(attrib, scale);
//        
//        world.display_objects.at(0).radians = world.getBearingToCursor(world.display_objects.at(0).location);
//        world.display_objects.at(1).radians = world.display_objects.at(0).radians;
        
//        for(int i = world.display_objects.size() - 1; i >= 1; i--) {
//            
//            DisplayObject& target = world.display_objects.at(i);
//            target.movement_behaviour(world, target);
//            target.setLocation(target.real_location, scale);
//            
//            if(target.lifecycle_conditions && target.lifecycle_conditions(world.display_objects.at(i))) {
//                world.display_objects.erase(world.display_objects.begin() + i);
//            }
//            
//        }
        
//        if(getLeftClickFlag()) {
//            DisplayObject bullet;
//            bullet.program = programs.at(0);
//            bullet.movement_behaviour = bullet_movement_behaviour;
//            bullet.lifecycle_conditions = bullet_lifecycle_condition;
//            
//            bullet.radians = world.display_objects.at(0).radians;
//            bullet.real_location[0] = world.display_objects.at(0).real_location[0];
//            bullet.real_location[1] = world.display_objects.at(0).real_location[1];
//            world.display_objects.push_back(bullet);
//            
//            for(int i = 0; i < 100; i++) {
//            basic_enemy.real_location[0] = ((float)rand()/(float)(RAND_MAX)) * 2 - 1;
//            basic_enemy.real_location[1] = ((float)rand()/(float)(RAND_MAX)) * 2 - 1;
//            
//            world.display_objects.push_back(basic_enemy);
//            }
//            resetLeftClickFlag();
//            std::cout << "Enemies: " << world.display_objects.size() - 2 << std::endl;
//        }
//        if(getRightClickFlag()) {
//            if(world.display_objects.size() > 2) {
//                world.display_objects.pop_back();
//            }
//            resetRightClickFlag();
//        }
        
//        world.scale_factor = (float) getScrollFlag() * 0.1f;
}