#ifndef LIGHTING_EXAMPLE_H
#define LIGHTING_EXAMPLE_H

#include "ExplorableSimulation.h"
#include "Cube.h"

class LightingExample: public ExplorableSimulation {
public:
    LightingExample() {

    };

    void run() {
        Cube cube;
        Cube light(
            "C:\\dev\\PowerGrid\\resources\\shaders\\simple_colorable.vs",
            "C:\\dev\\PowerGrid\\resources\\shaders\\simple_colorable.fs"
        );
        light.setAmbientLight(1.f);
        floorEnabled = true;


        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        float x_off = 0.f;
        float y_off = 2.f;
        int x_dir = 1;
        int y_dir = 1;

        initExplorableSimulation();

        while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) {


            if(glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) != GLFW_PRESS) {
                // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            stepThrough();

            glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f); 
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

            glm::mat4 model = glm::mat4(1.0f);
            // model = glm::translate(model, glm::vec3(x_off, y_off, -1.0f)); 
            // model = glm::rotate(model, (float) glfwGetTime() * glm::radians(60.f), glm::vec3(0.5f, 1.f, 0.f));
            
            model = glm::translate(model, glm::vec3(x_off, y_off, -2.0f));

            cube.setMats(model, camera.view, proj);
            cube.setAmbientLight(0.4f);
            cube.draw();

            glm::mat4 lModel = glm::mat4(1.0f);
            
            lModel = glm::translate(lModel, glm::vec3(1.2, 1.f, 2.f));
            light.setMats(lModel, camera.view, proj);
            light.setAmbientLight(1.f);
            light.draw();
            

            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
    }
};

#endif /* LIGHTING_EXAMPLE_H */