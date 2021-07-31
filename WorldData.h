//Include this everywhere






#ifndef WORLD_DATA_H
#define WORLD_DATA_H


#include "my_debug.h"

#include <chrono>
#include <vector>
#include "callbacks.h"

#include <ratio>
#include <functional>
#include <vector>

#include "glad/glad.h"
#include "glfw3.h"
#include "glm.hpp"

#include "Window.h"
#include "DisplayObject.h"

using namespace std::chrono;


class WorldData {
public:
    float mouseYaw;
    float mousePitch;
    

    //Flags
    int leftClickFlag;
    int rightClickFlag;
    int scrollFlag;
    float sensitivity;
    
    //Timing
    time_point<steady_clock>  previous_timestamp;
    time_point<steady_clock>  current_timestamp;
    time_point<steady_clock>  fps_timestamp;
    int fps;
    
    //Buffers
    GLuint worldVAO;
    GLuint worldVBO;
    unsigned int worldEBO;
    
    //Cursor
    double cursor_position[2];
    
    //Window information
    Window window;
    int width;
    int height;
    
    //Scaling factors
    float scale_factor;
    float x_scale;
    float y_scale;
    GLfloat scale[4];
    
    std::vector<DisplayObject> display_objects;
    
    
    /**
     * @brief Initialise the data about the world.
     * @return 
     */
    WorldData();
    
    ~WorldData();
    
    void initBuffers();
    
    
    /**
     * @brief Render all of the objects.
    **/
    void draw_objects();
    
    
    /**
     * @brief Set the World Data
     */
    void set_timer();
    
    /**
     * @brief Calculate timestep.
     * @return Timestep
     */
    int get_delta_t();
    
    
    /**
     * @brief Triggers fps handling
     * @return fps if its available, 0 otherwise.
     */
    int check_fps();
    
    //Note: need to pick when to scale things. The trouble comes from the fact that OpenGL considers the frame to be a square.
    
    
    /**
     * @brief Gets the cursor position and translates it into a float
     */
    void getCursorPosition();
    
    /**
     * @brief Get the bearing from an object to the cursor.
     * @param location
     * @return 
     */
    //Normalise because the frame treats a rectangle as a square for angles (45 degree corners).
    float getBearingToCursor(float location[]);
    
    
    
    
    float getBearing2D(float source[], float target[]);
    
    void setScale(float source[]);
    
    
    void init_window();
    
    void check_window();
    
    void calculate_timestep();
    
    //Mouse handler
    void  setMouseYaw(float _x);
    float getMouseYaw();
    void  setMousePitch(float _y);
    float getMousePitch();


    /**
     * @brief 
     * @param error
     * @param description
    **/
//    void basic_error_callback(int error, const char* description);
//
//
//    void close_on_unfocus(GLFWwindow* window, int focused);
//
//    //Options for handling inputs:
//    //For Maximum scalability, scancodes are ideal, though it may be expediant 
//    //to use a combination of keys, characters and scancodes to optimise processing
//    //https://www.glfw.org/docs/3.3/input_guide.html#input_keyboard
//    //int keyboardFlags[256];
//    //Range: 108 inputs between 32 and 348 inclusive.
//
//
//    //Key input handling: input of 1 prepares a response, input of 2 adapts the response, input of 0 releases the response.
//    //Easiest way to differentiate between handling of since press and a long press: only fire off on the release.
//
//    void general_keyboard_callback(
//            GLFWwindow* window, 
//            int key, 
//            int scancode, 
//            int action, 
//            int mods
//    );
//
//
//    void mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods);
//
//    int getLeftClickFlag();
//
//    void resetLeftClickFlag();
//
//    int getRightClickFlag();
//
//    void resetRightClickFlag();
//
//
//
//
//    int getScrollFlag();
//
//    void setScrollFlag(int val);
//
//    void scrollCallback(GLFWwindow* window, double x_offset, double y_offset);
//
//    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
//
//    void setCallbacks();
};

#endif /* WORLD_DATA_H */