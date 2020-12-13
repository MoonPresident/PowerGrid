//Include this everywhere
#include "my_debug.h"

#include <chrono>
#include "DisplayObject.h"
#include "BasicEnemy.h"

#include "glad/glad.h"
#include "glfw3.h"
#include "glm.hpp"





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
    
    //Buffers
    GLuint worldVAO;
    GLuint worldVBO;
    unsigned int worldEBO;
    
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
    GLfloat scale[4];
    
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
    
    ~WorldData() {
        glDeleteBuffers(1, &worldVAO);
    }
    
    void initBuffers() {
        glGenVertexArrays(1, &worldVAO);
        glBindVertexArray(worldVAO);
        
        glGenBuffers(1, &worldVBO);
        glBindBuffer(GL_ARRAY_BUFFER, worldVBO);
        glBufferData(GL_ARRAY_BUFFER,
                        1024*sizeof(float), 
                        0, 
                        GL_DYNAMIC_DRAW);
        
//        glGenBuffers(1, &worldEBO);
//        glNamedBufferStorage(worldEBO,
//                        1024*128,
//                        NULL,
//                        GL_MAP_WRITE_BIT);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, worldEBO);
        
//        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),  (void*) (6 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
//        glEnableVertexAttribArray(2);
        glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) 0); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
        glEnableVertexAttribArray(0);
        glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (4 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
        glEnableVertexAttribArray(1);
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float),  (void*) (8 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
        glEnableVertexAttribArray(2);
        
    }
    
    
    /**
     * @brief Render all of the objects.
    **/
    void draw_objects() {
        
        unsigned int offset = 0;
        //Setting this up will require math.
        //This needs to be broken up into the different spaces (i.e. local, world and view).
        //Then, you need to work out whats being handed out. Vertical and horizontal rotation? Vertices? Colours?
        //Use some hash defines to figure this out. Most importantly, work out how to generalise this.
        
        glBindVertexArray(worldVAO);
//        glBindBuffer(GL_ARRAY_BUFFER,  worldVBO);
        for(auto draw_object: display_objects) {
            
            
            //VBO Method.
            float vertices[9];
            vertices[0] = x_scale;
            vertices[1] = y_scale;
            vertices[2] = 0;
            vertices[3] = 0;
            
            for(int i = 0; i < 4; i++) {
                vertices[i + 4] = draw_object.location[i];
            }
            vertices[8] = draw_object.radians;
            
            glBufferSubData(GL_ARRAY_BUFFER, offset, 9*sizeof(float), vertices);
            
            offset += sizeof(vertices);
            
//            unsigned int indices[] = {
//                0 + vertex_offset, 1 + vertex_offset, 3 + vertex_offset,
//                1 + vertex_offset, 2 + vertex_offset, 3 + vertex_offset
//            };
//        for(int i = 0; i < 8; i++) std::cout << vertices[i] << ", ";
//        std::cout << vertices[8] << std::endl;
        std::cout << "ERROR: " << glGetError() << std::endl;
//        break;
        }
        auto target = (display_objects.at(0));
        glUseProgram(target.program.ID);
        
//        glBindVertexArray(worldVAO);

//        std::cout << scale[0] << ", " << scale[1] << ", " << scale[2] << ", " << scale[3] << ", ";
//        std::cout << target.location[0] << ", " << target.location[1] << ", " << target.location[2] << ", " << target.location[3] << ", " << target.radians << std::endl;
//        glVertexAttrib4fv(0, scale);
//        glVertexAttrib4fv(1, target.location);
//        glVertexAttrib1f(2, target.radians);
        glDrawArrays(target.program.drawType, 0, 4);//* display_objects.size());
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
    
    void setScale(float source[]) {
        for(int i = 0; i < 4; i++) scale[i] = source[i];
    }
    
    
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