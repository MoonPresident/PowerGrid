#ifndef EXPLORABLE_SIMULATION_H
#define EXPLORABLE_SIMULATION_H

// #include "AbstractSimulation.h"
#include "WorldData.h"
#include "Camera.h"

#include "TiledFloor.h"

class ExplorableSimulation: public WorldData {
public:

    Camera camera;
    float moveSpeed;
    float jumpVelocity;
    glm::vec3 force_vector; //x, y, z
    float pc_z_pos;

    TiledFloor floor;

    ExplorableSimulation(): force_vector(0.f, 0.f, 0.f) {};
    ~ExplorableSimulation() {};

    void initExplorableSimulation() {
        moveSpeed = 5.f;
        jumpVelocity = 2.8f;

        pc_z_pos = 1.f;
        
        glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        setCallbacks(window.getWindow());

        setMouseOffsetX(0.f);
        setMouseOffsetY(0.f);
        setMouseLastY(height / 2.f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        camera.model = glm::translate(camera.model, glm::vec3(0.f, 1.f, 0.f));
    }

    void stepThrough() {
        //Trigger new timestep
        calculate_timestep();
        
        float delta_t = get_delta_t()  / 1000000.f;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        scale_factor = (float) getScrollFlag() * 0.1f;
        
        //Track FPS.
        auto fps = check_fps();
        //Things to be done once a second.
        if(fps) { std::cout << "FPS: " << fps << std::endl; }
        float newYaw    = getMouseYaw() - getMouseOffsetX() * sensitivity;
        float newPitch  = getMousePitch() + getMouseOffsetY() * sensitivity;
        if(newPitch < -89.0f) newPitch = -89.f;
        else if (newPitch > 89.0f) newPitch = 89.f;
        setMouseYaw(newYaw);
        setMousePitch(newPitch);
        setMouseOffsetX(0.f);
        setMouseOffsetY(0.f);
        
        
        glm::vec3 direction;
        direction.x = cos(glm::radians(mouseYaw)) * cos(glm::radians(mousePitch));
        direction.y = sin(glm::radians(mousePitch));
        direction.z = sin(glm::radians(mouseYaw)) * cos(glm::radians(mousePitch));
        camera.cameraFront = glm::normalize(direction);

        check_window();
     
        const float cameraSpeed = moveSpeed * delta_t; // adjust accordingly
        if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
            camera.cameraPos += cameraSpeed * glm::vec3(camera.cameraFront.x, 0.f, camera.cameraFront.z);
        if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
            camera.cameraPos -= cameraSpeed * glm::vec3(camera.cameraFront.x, 0.f, camera.cameraFront.z);
        if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
            camera.cameraPos -= glm::normalize(glm::cross( glm::vec3(camera.cameraFront.x, 0.f, camera.cameraFront.z), camera.cameraUp)) * cameraSpeed;
        if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
            camera.cameraPos += glm::normalize(glm::cross( glm::vec3(camera.cameraFront.x, 0.f, camera.cameraFront.z), camera.cameraUp)) * cameraSpeed;
        if(glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) && force_vector.z == 0.f) {
            force_vector.z = jumpVelocity;// m/s
        }
        camera.cameraPos = glm::vec3(camera.cameraPos.x, pc_z_pos, camera.cameraPos.z);
        
        force_vector.z -= 9.8f * delta_t;
        pc_z_pos += force_vector.z * delta_t;
        if(pc_z_pos < 1.f) {
            pc_z_pos = 1.f;
            force_vector.z = 0.f;
        }
        
        camera.view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);

        floor.setMats(glm::mat4(1.0f), camera.view, camera.projection);
        floor.setAmbientLight(1.f);
        floor.draw();
    }
};

#endif /* EXPLORABLE_SIMULATION_H */