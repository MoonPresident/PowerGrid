

#ifndef ABSTRACT_SIMULATION_H
#define ABSTRACT_SIMULATION_H


#include <chrono>

#include "Window.h"

#include "glad/glad.h"
#include "glfw3.h"
#include "glm.hpp"

class AbstractSimulation {
public:
//    float mouseYaw;
//    float mousePitch;
//    
//
//    //Flags
//    int leftClickFlag;
//    int rightClickFlag;
//    int scrollFlag;
//    float sensitivity;
//    
//    //Timing
//    time_point<steady_clock>  previous_timestamp;
//    time_point<steady_clock>  current_timestamp;
//    time_point<steady_clock>  fps_timestamp;
//    int fps;
//    
//    //Buffers
//    GLuint worldVAO;
//    GLuint worldVBO;
//    unsigned int worldEBO;
//    
//    //Cursor
//    double cursor_position[2];
//    
    //Window information
    Window window;
    int width;
    int height;
    
    //Scaling factors
    float scale_factor;
    float x_scale;
    float y_scale;
    GLfloat scale[4];
//    
//    std::vector<DisplayObject> display_objects;
//    std::vector<GLfloat> display_object_coords;

    void init_window();
    
    void check_window();
    
    virtual void run()=0;
    
    AbstractSimulation();
    virtual ~AbstractSimulation();
    
//    void calculate_timestep();
    
//    virtual void initBuffers()=0;
    
    
//    /**
//     * @brief Render all of the objects.
//    **/
//    void draw_objects();
//    
//    
//    /**
//     * @brief Set the World Data
//     */
//    void set_timer();
//    
//    /**
//     * @brief Calculate timestep.
//     * @return Timestep
//     */
//    int get_delta_t();
//    
//    
//    /**
//     * @brief Triggers fps handling
//     * @return fps if its available, 0 otherwise.
//     */
//    int check_fps();
//    
//    //Note: need to pick when to scale things. The trouble comes from the fact that OpenGL considers the frame to be a square.
//    
//    
//    /**
//     * @brief Gets the cursor position and translates it into a float
//     */
//    void getCursorPosition();
//    
//    /**
//     * @brief Get the bearing from an object to the cursor.
//     * @param location
//     * @return 
//     */
//    //Normalise because the frame treats a rectangle as a square for angles (45 degree corners).
//    float getBearingToCursor(float location[]);
//    
//    
//    
//    
//    float getBearing2D(float source[], float target[]);
//    
//    void setScale(float source[]);
//    
//    //Mouse handler
//    void  setMouseYaw(float _x);
//    float getMouseYaw();
//    void  setMousePitch(float _y);
//    float getMousePitch();
};

#endif /* ABSTRACT_SIMULATION_H */