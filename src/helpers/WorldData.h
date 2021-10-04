//Include this everywhere

#ifndef WORLD_DATA_H
#define WORLD_DATA_H


#include "my_debug.h"

#include <vector>
#include "callbacks.h"

#include <ratio>
#include <functional>
#include <vector>

#include "glad/glad.h"
#include "glfw3.h"
#include "glm.hpp"

#include "DisplayObject.h"

#include "AbstractSimulation.h"

using namespace std::chrono;


class WorldData: public AbstractSimulation {
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
    
    std::vector<DisplayObject> display_objects;
    std::vector<GLfloat> display_object_coords;
    
    
    /**
     * @brief Initialise the data about the world.
     * @return 
     */
    WorldData();
    
    virtual ~WorldData();
    
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
     
    void calculate_timestep();
    
    void run();
    
    //Mouse handler
    void  setMouseYaw(float _x);
    float getMouseYaw();
    void  setMousePitch(float _y);
    float getMousePitch();

};

#endif /* WORLD_DATA_H */