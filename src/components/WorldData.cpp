    
    
#include "WorldData.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

/**
 * @brief Initialise the data about the world.
 * @return 
 */
WorldData::WorldData() {
    //Set up time step and fps timestamp
    fps = 0;
    current_timestamp = steady_clock::now();
    previous_timestamp = current_timestamp;
    fps_timestamp = current_timestamp;
    
    mousePitch = 0.f;
    mouseYaw = -90.f;
    sensitivity = 0.1f;
    
    initBuffers();
};

WorldData::~WorldData() {
    glDeleteBuffers(1, &worldVAO);
};

void WorldData::initBuffers() {
    glGenVertexArrays(1, &worldVAO);
    glBindVertexArray(worldVAO);
    
    glGenBuffers(1, &worldVBO);
    glBindBuffer(GL_ARRAY_BUFFER, worldVBO);
    glBufferData(GL_ARRAY_BUFFER,
                    9*sizeof(float), 
                    display_object_coords.data(),//0, 
                    GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) 0); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (4 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float),  (void*) (8 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(0, 1);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    
};


/**
 * @brief Render all of the objects.
**/
void WorldData::draw_objects() {
        unsigned int offset = 0;
        //Setting this up will require math.
        //This needs to be broken up into the different spaces (i.e. local, world and view).
        //Then, you need to work out whats being handed out. Vertical and horizontal rotation? Vertices? Colours?
        //Use some hash defines to figure this out. Most importantly, work out how to generalise this.

        glBindVertexArray(worldVAO);
        glBindBuffer(GL_ARRAY_BUFFER,  worldVBO);

        #if defined debug_all || defined debug_shader
        std::cout << "ERROR: ";
        #endif

        glBufferData(GL_ARRAY_BUFFER,
                display_objects.size() * 9*sizeof(float), 
                0, 
                GL_DYNAMIC_DRAW);

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

            for(int i = 0; i < 9; i++) display_object_coords.at(i + offset) = vertices[i];
            
            //This is an incorrect usage of this.
            glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), 9*sizeof(float), vertices);

            #if defined debug_all || defined debug_shader
            std::cout << glGetError() << ": ";
            #endif  

            offset += 9;

            // unsigned int indices[] = {
            //     0 + vertex_offset, 1 + vertex_offset, 3 + vertex_offset,
            //     1 + vertex_offset, 2 + vertex_offset, 3 + vertex_offset
            // };
            // for(int i = 0; i < 8; i++) std::cout << vertices[i] << ", ";
            // std::cout << vertices[8] << std::endl;
            

        }
        std::cout << 5 << std::endl;

//        glBindVertexArray(worldVAO);
        
//        for(int i = 0; i < 2; i++) {
        // std::cout << "SIZE: " << display_objects.size() << std::endl;
        for(int i = 0; i < display_objects.size(); i++) {
            glUseProgram(display_objects.at(i).program.ID);
            
            glVertexAttrib4fv(0, scale);
            glVertexAttrib4fv(1, display_objects.at(i).location);
            glVertexAttrib1f(2, display_objects.at(i).radians);
            glDrawArrays(display_objects.at(i).program.drawType, 0, 6);
        }
        
        
//        auto target = (display_objects.at(0));
//        glUseProgram(target.program.ID);
//
//        glVertexAttrib4fv(0, scale);
//        glVertexAttrib4fv(1, target.location);
//        glVertexAttrib1f(2, target.radians);
//        glDrawArraysInstanced(GL_TRIANGLES, 0, 9, display_objects.size());

//        std::cout << scale[0] << ", " << scale[1] << ", " << scale[2] << ", " << scale[3] << ", ";
//        std::cout << target.location[0] << ", " << target.location[1] << ", " << target.location[2] << ", " << target.location[3] << ", " << target.radians << std::endl;
        
//        glVertexAttrib4fv(0, scale);
//        glVertexAttrib4fv(1, target.location);
//        glVertexAttrib1f(2, target.radians);
//        glDrawArrays(target.program.drawType, 0, 4 * display_objects.size());
        
        
        
        //Previous implementation:
//        glVertexAttrib4fv(0, attrib);
//        for(auto program: programs) {
//            glUseProgram(program.ID);
//            
//            glUniform1i(1, variant);
//            glUniformMatrix4fv(2, 1, GL_FALSE, scale);
//            
//            glUniform1f(3, radians);
//
//            glDrawArrays(program.drawType, 0, 4);
//        }

};


/**
 * @brief Set the World Data
 */
void WorldData::set_timer() {
    current_timestamp = steady_clock::now();
};

/**
 * @brief Calculate timestep.
 * @return Timestep
 */
int WorldData::get_delta_t() {
    previous_timestamp = current_timestamp;
    current_timestamp = steady_clock::now();
    
    return duration_cast<microseconds>(current_timestamp - previous_timestamp).count();
};


/**
 * @brief Triggers fps handling
 * @return fps if its available, 0 otherwise.
 */
int WorldData::check_fps() {
    auto delta_fps = duration_cast<seconds>(current_timestamp - fps_timestamp).count();
    auto fps_output = 0;
    
    if(delta_fps) {
        fps_timestamp = current_timestamp;
        fps_output = fps;
        fps = 0;
    }
    
    fps++;
    return fps_output;
};

//Note: need to pick when to scale things. The trouble comes from the fact that OpenGL considers the frame to be a square.


/**
 * @brief Gets the cursor position and translates it into a float
 */
void WorldData::getCursorPosition() {
    glfwGetCursorPos(window.getWindow(), cursor_position, cursor_position + 1);
    
    cursor_position[1] = (2 * (cursor_position[1] / (float) height) - 1) * x_scale;
    cursor_position[0] = (2 * (cursor_position[0] / (float) width) - 1) * y_scale;
};

/**
 * @brief Get the bearing from an object to the cursor.
 * @param location
 * @return 
 */
//Normalise because the frame treats a rectangle as a square for angles (45 degree corners).
float WorldData::getBearingToCursor(float location[]) {
    float x_span = cursor_position[1] + location[1] * x_scale;
    float y_span = cursor_position[0] - location[0] * y_scale;
    
    return (float) atan(x_span / y_span) + (y_span < 0) * M_PI;
};




float WorldData::getBearing2D(float source[], float target[]) {
    float x_span = 0 - (target[1] - source[1]) * x_scale;
    float y_span = (target[0] - source[0]) * y_scale;
    
    return (float) atan(x_span / y_span) + (y_span < 0) * M_PI;
};

void WorldData::setScale(float source[]) {
    for(int i = 0; i < 4; i++) scale[i] = source[i];
};

void WorldData::calculate_timestep() {
    getCursorPosition();
};

void WorldData::run() {
    std::cout << "running "; 
}

//Mouse handler
void WorldData::setMouseYaw(float _x) {
    mouseYaw = _x;
}

void WorldData::setMousePitch(float _y) {
    mousePitch = _y;
}

float WorldData::getMouseYaw() {
    return mouseYaw;
}

float WorldData::getMousePitch() {
    return mousePitch;
}