/**
 * Author: MoonPresident
 * Date: August 31st 2021
 * 
 * Game sequence for squares.
 */

#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "DisplayObject.h"
#include "WorldData.h"
#include "Camera.h"

#include "squares_original.h"


#define SQRT_2 1.4142

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

SquaresOriginal::SquaresOriginal() {

}

SquaresOriginal::~SquaresOriginal() {

}

int squares_original_game() {
    GLuint vao;
    float moveSpeed = 5.f;
    float jumpVelocity = 2.8f;
    
    WorldData world; 
    
    std::cout << "here";
    Camera camera;
    setCallbacks(world.window.getWindow());
    setMouseOffsetX(0.f);
    setMouseOffsetY(0.f);
    setMouseLastY(world.height / 2.f);
    world.init_window();
    
    std::vector<Program> programs = loadPrograms();
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLint variant = 0;
    float scale_coeff = 1.f;
    
    std::cout << "Creating objects: " << programs.size() << std::endl;
    DisplayObject pcObject, pcLine;
    pcObject.program = programs.at(0);
    pcLine.program   = programs.at(1);
    world.display_objects.push_back(pcObject);
    world.display_objects.push_back(pcLine);
    
    for (int k = 0; k < 18; k++) world.display_object_coords.push_back(0.f);
    
    DisplayObject basic_enemy;
    basic_enemy.program = programs.at(0);
    basic_enemy.movement_behaviour = basic_enemy_movement_behaviour;
    basic_enemy.real_location[0] = -0.5f;
    basic_enemy.real_location[1] = -0.5f;
    
    for(int i = 0; i < 4; i++) {
        basic_enemy.real_location[i % 2] *= -1.f;
        world.display_objects.push_back(basic_enemy);
        for (int k = 0; k < 9; k++) world.display_object_coords.push_back(0.f);
    }
    
    #ifdef debug_all
    std::cout << "Done." << std::endl;
    #endif
    
    while(!glfwWindowShouldClose(world.window.getWindow())) {
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
        
        int y_direction = glfwGetKey(world.window.getWindow(), GLFW_KEY_W) - glfwGetKey(world.window.getWindow(), GLFW_KEY_S);
        int x_direction = glfwGetKey(world.window.getWindow(), GLFW_KEY_D) - glfwGetKey(world.window.getWindow(), GLFW_KEY_A);
        
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
            
            for (int k = 0; k < 9; k++) world.display_object_coords.push_back(0.f);
            
            for(int i = 0; i < 100; i++) {
                basic_enemy.real_location[0] = ((float)rand()/(float)(RAND_MAX)) * 2 - 1;
                basic_enemy.real_location[1] = ((float)rand()/(float)(RAND_MAX)) * 2 - 1;
                
                world.display_objects.push_back(basic_enemy);
                
                for (int k = 0; k < 9; k++) world.display_object_coords.push_back(0.f);
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
//        glVertexAttrib4fv(0, scale);
        
        world.draw_objects();
        
        glfwSwapBuffers(world.window.getWindow());
        glfwPollEvents();
    }
    
    //Close up shop
    glDeleteVertexArrays(1, &vao);
    for(auto program: programs) {
        glDeleteProgram(program.ID);
    }
    glDeleteVertexArrays(1, &vao);
    
    glfwTerminate();
    std::cout << "Program successfully terminated." << std::endl;
	return 0;
}