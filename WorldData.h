//Include this everywhere
#include "debug.h"

#include <chrono>
#include "DisplayObject.h"
#include "BasicEnemy.h"

#include "glad/glad.h"
#include "glfw3.h"





#ifndef WORLD_DATA_H
#define WORLD_DATA_H




using namespace std::chrono;

class WorldData {
public:
    //Timing
    time_point<steady_clock>  previous_timestamp;
    time_point<steady_clock>  current_timestamp;
    time_point<steady_clock>  fps_timestamp;
    int fps;
    
    //Cursor
    double cursor_position[2];
    
    //Window information
    GLFWwindow* window;
    int width;
    int height;
    
    //Scaling factors
    float scale_factor;
    float x_scale;
    float y_scale;
    
    //Display Object
    std::vector<DisplayObject> display_objects;
    
    
    /**
     * @brief Initialise the data about the world.
     * @return 
     */
    WorldData() {
        //Set up time step and fps timestamp
        fps = 0;
        current_timestamp = steady_clock::now();
        previous_timestamp = current_timestamp;
        fps_timestamp = current_timestamp;
    }
    
    
    void draw_objects() {
        for(auto draw_object: display_objects) {
            glUseProgram(draw_object.program.ID);
            
            glVertexAttrib4fv(1, draw_object.location);
            glUniform1i(2, 0);//variant
            glUniform1f(3, draw_object.radians);

            glDrawArrays(draw_object.program.drawType, 0, 5);
        }
    }
    
    
    /**
     * @brief Set the World Data
     */
    void set_timer() {
        current_timestamp = steady_clock::now();
    }
    
    /**
     * @brief Calculate timestep.
     * @return Timestep
     */
    int get_delta_t() {
        previous_timestamp = current_timestamp;
        current_timestamp = steady_clock::now();
        
        return duration_cast<microseconds>(current_timestamp - previous_timestamp).count();
    }
    
    
    /**
     * @brief Triggers fps handling
     * @return fps if its available, 0 otherwise.
     */
    int check_fps() {
        auto delta_fps = duration_cast<seconds>(current_timestamp - fps_timestamp).count();
        auto fps_output = 0;
        
        if(delta_fps) {
            fps_timestamp = current_timestamp;
            fps_output = fps;
            fps = 0;
        }
        
        fps++;
        return fps_output;
    }
    
    //Note: need to pick when to scale things. The trouble comes from the fact that OpenGL considers the frame to be a square.
    
    
    /**
     * @brief Gets the cursor position and translates it into a float
     */
    void getCursorPosition() {
        glfwGetCursorPos(window, cursor_position, cursor_position + 1);
        
        cursor_position[1] = (2 * (cursor_position[1] / (float) height) - 1) * x_scale;
        cursor_position[0] = (2 * (cursor_position[0] / (float) width) - 1) * y_scale;
    }
    
    /**
     * @brief Get the bearing from an object to the cursor.
     * @param location
     * @return 
     */
    //Normalise because the frame treats a rectangle as a square for angles (45 degree corners).
    float getBearingToCursor(float location[]) {
        float x_span = cursor_position[1] + location[1] * x_scale;
        float y_span = cursor_position[0] - location[0] * y_scale;
        
        return (float) atan(x_span / y_span) + (y_span < 0) * M_PI;
    }
    
    
    
    
    float getBearing2D(float source[], float target[]) {
        float x_span = 0 - (target[1] - source[1]) * x_scale;
        float y_span = (target[0] - source[0]) * y_scale;
        
        return (float) atan(x_span / y_span) + (y_span < 0) * M_PI;
    }
    
    void getBearing2D() {
        
    };
    
    
    
    void init_window() {
        //Set window and scale.
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        scale_factor = 1.f;
        x_scale = scale_factor * ((width != height) * (float) height / (float) width + (width == height));
        y_scale = scale_factor;
    }
    
    void check_window() {
        int prev_width = width;
        int prev_height = height;
        glfwGetFramebufferSize(window, &width, &height);
        
//        if(prev_width == width && prev_height == height) {
//            return;
//        }
        
        glViewport(0, 0, width, height);
        x_scale = scale_factor * ((width != height) * (float) height / (float) width + (width == height));
        y_scale = scale_factor;
    }
    
    void calculate_timestep() {
        getCursorPosition();
    }
};

#endif /* WORLD_DATA_H */