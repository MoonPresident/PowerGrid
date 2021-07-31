    
    
#include "WorldData.h"
#include <iostream>

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
                    1024*sizeof(float), 
                    0, 
                    GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) 0); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (4 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float),  (void*) (8 * sizeof(float))); //Pointer specifies offset of the first component of the first generic vertex attribute. Jesus.
    glEnableVertexAttribArray(2);
    
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

        glBindVertexArray(worldVAO);

//        std::cout << scale[0] << ", " << scale[1] << ", " << scale[2] << ", " << scale[3] << ", ";
//        std::cout << target.location[0] << ", " << target.location[1] << ", " << target.location[2] << ", " << target.location[3] << ", " << target.radians << std::endl;
        glVertexAttrib4fv(0, scale);
        glVertexAttrib4fv(1, target.location);
        glVertexAttrib1f(2, target.radians);
        glDrawArrays(target.program.drawType, 0, 4* display_objects.size());
        
        
        
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
//        attrib[0] = -0.5f;
//        attrib[1] = -0.5f;
//
//        glVertexAttrib4fv(0, attrib);
//        glUseProgram(programs.at(0).ID);
//        glUniform1i(1, variant);
//        glUniformMatrix4fv(2, 1, GL_FALSE, scale);
//
//        glUniform1f(3, radians);
//
//        glDrawArrays(programs.at(0).drawType, 0, 4);
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


void WorldData::init_window() {
    //Set window and scale.
    glfwGetFramebufferSize(window.getWindow(), &width, &height);
    glViewport(0, 0, width, height);
    scale_factor = 1.f;
    x_scale = scale_factor * ((width != height) * (float) height / (float) width + (width == height));
    y_scale = scale_factor;
};

void WorldData::check_window() {
    int prev_width = width;
    int prev_height = height;
    glfwGetFramebufferSize(window.getWindow(), &width, &height);
    
//        if(prev_width == width && prev_height == height) {
//            return;
//        }
    
    glViewport(0, 0, width, height);
    x_scale = scale_factor * ((width != height) * (float) height / (float) width + (width == height));
    y_scale = scale_factor;
};

void WorldData::calculate_timestep() {
    getCursorPosition();
};


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




/********************************************************************************
 *******                             Callbacks                            *******
********************************************************************************/


/**
 * @brief 
 * @param error
 * @param description
**/
//void WorldData::basic_error_callback(int error, const char* description){
//    fputs(description, stderr);
//}
//
//
//void WorldData::close_on_unfocus(GLFWwindow* window, int focused) {
//    if(!focused) {
//        glfwSetWindowShouldClose(window, 1);
//    }
//}
//
////Options for handling inputs:
////For Maximum scalability, scancodes are ideal, though it may be expediant 
////to use a combination of keys, characters and scancodes to optimise processing
////https://www.glfw.org/docs/3.3/input_guide.html#input_keyboard
////int keyboardFlags[256];
////Range: 108 inputs between 32 and 348 inclusive.
//
//
////Key input handling: input of 1 prepares a response, input of 2 adapts the response, input of 0 releases the response.
////Easiest way to differentiate between handling of since press and a long press: only fire off on the release.
//
//void WorldData::general_keyboard_callback(
//        GLFWwindow* window, 
//        int key, 
//        int scancode, 
//        int action, 
//        int mods
//) {
//    
//    #ifdef debug_all
//    std::cout << "Key: " << key << (char) key << ", Scancode: " << scancode << std::endl;
//    std::cout << "Action: " << action << ", mods: " << mods << std::endl;
//    #endif
//}
//
//
//void WorldData::mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods) {
//    if(action) {
//        #ifdef debug_all
//        std::cout  << "Button: " << button << "Action: " << action  << "Mods: " <<  mods << std::endl << std::endl;
//        #endif
//        if(button == 0) {
//            leftClickFlag = 1;
//        } else if(button == 1) {
//            rightClickFlag = 1;
//        }
//    }
//}
//
//int WorldData::getLeftClickFlag() {
//    return leftClickFlag;
//}
//
//void WorldData::resetLeftClickFlag() {
//    leftClickFlag = 0;
//}
//
//int WorldData::getRightClickFlag() {
//    return rightClickFlag;
//}
//
//void WorldData::resetRightClickFlag() {
//    rightClickFlag = 0;
//}
//
//int WorldData::getScrollFlag() {
//    return scrollFlag;
//}
//
//void WorldData::setScrollFlag(int val) {
//    if(val < 1) {
//        scrollFlag = 1;
//    } else {
//        scrollFlag = val;
//    }
//}
//
//void WorldData::scrollCallback(GLFWwindow* window, double x_offset, double y_offset) {
//    scrollFlag += y_offset;
//    if(scrollFlag < 1) scrollFlag = 1;
//    
//    #ifdef debug_all
//    std::cout << "XY: " << x_offset << " " << y_offset << std::endl;
//    #endif
//}
//
//void WorldData::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
//    offsetMouseX = xpos - lastMouseX;
//    offsetMouseY = ypos - lastMouseY;
//};




/********************************************************************************
 *******                        Callbacks Wrappers                        *******
********************************************************************************/

//void wrapped_basic_error_callback(int error, const char* description){
//    WorldData::basic_error_callback(error, description);
//}
//
//
//void wrapped_close_on_unfocus(GLFWwindow* window, int focused) {
//    WorldData::close_on_unfocus(window, focused);
//}
//
////Options for handling inputs:
////For Maximum scalability, scancodes are ideal, though it may be expediant 
////to use a combination of keys, characters and scancodes to optimise processing
////https://www.glfw.org/docs/3.3/input_guide.html#input_keyboard
////int keyboardFlags[256];
////Range: 108 inputs between 32 and 348 inclusive.
//
//
////Key input handling: input of 1 prepares a response, input of 2 adapts the response, input of 0 releases the response.
////Easiest way to differentiate between handling of since press and a long press: only fire off on the release.
//
//void wrapped_general_keyboard_callback(
//        GLFWwindow* window, 
//        int key, 
//        int scancode, 
//        int action, 
//        int mods
//) {
//    WorldData::general_keyboard_callback(GLFWwindow* window, key, scancode, action, mods);
//}
//
//
//void wrapped_mousebutton_flag_callback(GLFWwindow* window, int button, int action, int mods) {
//    WorldData::mousebutton_flag_callback(window, button, action, mods);
//}
//
//int wrapped_getLeftClickFlag() {
//    WorldData::getLeftClickFlag();
//}
//
//void wrapped_resetLeftClickFlag() {
//    WorldData::resetLeftClickFlag();
//}
//
//int wrapped_getRightClickFlag() {
//    WorldData::getRightClickFlag();
//}
//
//void wrapped_resetRightClickFlag() {
//    WorldData::resetRightClickFlag();
//}
//
//int wrapped_getScrollFlag() {
//    WorldData::getScrollFlag();
//}
//
//void wrapped_setScrollFlag(int val) {
//    WorldData::setScrollFlag(val);
//}
//
//void wrappedScrollCallback(GLFWwindow* window, double x_offset, double y_offset) {
//    WorldData::scrollCallback(window, x_offset, y_offset);
//}
//
//void wrappedMouseCallback(GLFWwindow* window, double xpos, double ypos) {
//    WorldData::mouseCallback(window, xpos, ypos);
//};
//
///**
// * @brief 
// * @param frame
// */
//void WorldData::setCallbacks() {
//    glfwMakeContextCurrent(window);
//    glfwSetWindowFocusCallback(window, wrapped_close_on_unfocus);
//    glfwSetMouseButtonCallback(window, wrapped_mousebutton_flag_callback);
//    glfwSetScrollCallback(window, wrappedScrollCallback);
//    glfwSetKeyCallback(window, wrapped_general_keyboard_callback);
//    
//    
//    //Mouse callback
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    glfwSetCursorPosCallback(window, wrappedMouseCallback);
//}