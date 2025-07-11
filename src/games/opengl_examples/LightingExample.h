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
            "C:/dev/PowerGrid/resources/shaders/simple_colorable.vs",
            "C:/dev/PowerGrid/resources/shaders/simple_colorable.fs"
        );
        floorEnabled = false;

        glm::mat4 cubeModel = glm::mat4(1.0f);
        glm::vec3 cubeOffset = glm::vec3(8.f, 2.f, 8.f);
        glm::vec3 cubeScale = glm::vec3(4.f, 4.f, 4.f);
        cubeModel = glm::translate(cubeModel, cubeOffset);
        cubeModel = glm::scale(cubeModel, cubeScale);

        initExplorableSimulation();

        while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) {


            if(glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) != GLFW_PRESS) {
                //This is not working because the lower level function now clears the buffer first.
                // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            stepThrough();

            glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f); 

            //Scaling and offset are permanent so do them outside of the loop.
            // cubeModel = glm::translate(cubeModel, cubeOffset);
            // cubeModel = glm::scale(cubeModel, cubeScale);
            glm::mat4 model = glm::rotate(cubeModel, (float) glfwGetTime() * glm::radians(60.f), glm::vec3(0.5f, 1.f, 0.f));

            glm::vec3 lightPos(1.2, 1.f, 2.f);
            glm::mat4 lModel = glm::mat4(1.0f);
            lModel = glm::scale(lModel, glm::vec3(0.2f, 0.2f, 0.2f));
            lModel = glm::translate(lModel, lightPos);

            GLint program = cube.shader.ID;
            glm::vec3 lightColor(0.5f, 0.f, 1.0f);
            glUseProgram(program);
            int modelLoc = glGetUniformLocation(program, "model");
            int viewLoc = glGetUniformLocation(program, "view");
            int projLoc = glGetUniformLocation(program, "projection");
            int ambientLightLoc = glGetUniformLocation(program, "ambientLight");
            int colorLoc = glGetUniformLocation(program, "colorIn");
            int offsetLoc = glGetUniformLocation(program, "aOffset");
            int lightPosLoc = glGetUniformLocation(program, "lightPos");
            int lightColorLoc = glGetUniformLocation(program, "lightColor");
            int viewPosLoc = glGetUniformLocation(program, "viewPos");

            
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
            glUniform1f(ambientLightLoc, 0.1f);
            glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(1.f, 1.f, 1.f, 1.f)));
            glUniform3fv(offsetLoc, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
            glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
            glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
            glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.cameraPos));


            cube.draw();
            program = light.shader.ID;
            glUseProgram(light.shader.ID);
            modelLoc = glGetUniformLocation(program, "model");
            viewLoc = glGetUniformLocation(program, "view");
            projLoc = glGetUniformLocation(program, "projection");
            colorLoc = glGetUniformLocation(program, "colorIn");
            offsetLoc = glGetUniformLocation(program, "aOffset");
            
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lModel));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
            glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(1.f, 1.f, 1.f, 1.f)));
            glUniform3fv(offsetLoc, 1, glm::value_ptr(glm::vec3(10.f, 0.f, 0.f)));
            light.draw();

            finalFunctions();

            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
    }
};

#endif /* LIGHTING_EXAMPLE_H */