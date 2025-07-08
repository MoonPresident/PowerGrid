#ifndef CAMERAEXAMPLE_H
#define CAMERAEXAMPLE_H

#include "WorldData.h"

bool exampleFirstMouse;
float lastX = 400, lastY = 300;

float yaw = -90.0f;
float pitch = 0.f;
float fov = 45.f;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);



void example_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (exampleFirstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        exampleFirstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

class CameraExample : public WorldData
{
public:
    CameraExample() {
        #ifdef debug_all
        std::cout << "Camera example created." << std::endl;
        #endif
        
        glfwSetCursorPosCallback(window.getWindow(), example_mouse_callback);  
    }
    
    void run() override {
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
        
        glm::mat4 view;
        
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
                   glm::vec3(0.0f, 0.0f, 0.0f), 
                   glm::vec3(0.0f, 1.0f, 0.0f));
        
        GLuint vao, vbo, ebo;
        glGenVertexArrays(1, &vao);        
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        float deltaTime = 0.0f;	// Time between current frame and last frame
        float lastFrame = 0.0f; // Time of last frame
        
        glBindVertexArray(vao);
        glEnable(GL_DEPTH_TEST);

        
        static const GLfloat vertexData[] = {
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // front top right
             0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // front bottom right
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // front bottom left
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // front top left 
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // back  top right
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // back  bottom right
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // back  bottom left
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // back  top left 
        };
        
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3,
            4, 5, 7,
            5, 6, 7,
            
            0, 4, 3,
            4, 7, 3,
            1, 5, 2,
            5, 2, 6,
            
            0, 4, 1,
            4, 5, 1,
            3, 7, 2,
            7, 6, 2,
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        ShaderStore shader;
        shader.addShader("C:\\dev\\PowerGrid\\resources\\shaders\\transform_3d_vertex_shader.txt", GL_VERTEX_SHADER);
        shader.addShader("C:\\dev\\PowerGrid\\resources\\shaders\\texture_2d_fragment_shader.txt", GL_FRAGMENT_SHADER);
        
        GLuint program = glCreateProgram();
        shader.linkProgram(program);
        
        TextureFactory texFactory;
        GLuint tex = texFactory.getTexture(".\\resources\\textures\\stock_images\\fish_eyes.jpg");
        glBindTexture(GL_TEXTURE_2D, tex);
        
        float x_off[2] = {0.f, -1.};
        float y_off[2] = {0.f, -1.f};
        int x_dir[2] = {0, 1};
        int y_dir[2] = {1, 1};
        
        //This captures the escape key.
        glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            
            float cameraSpeed = 2.5f * deltaTime;
            if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
                cameraPos += cameraSpeed * cameraFront;
            if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
                cameraPos -= cameraSpeed * cameraFront;
            if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            
            
            
            
            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            cameraFront = glm::normalize(direction);
            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            
            //3D stuff.
            glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
            glm::mat4 model = glm::mat4(1.0f);
            
            glm::mat4 view = glm::mat4(1.0f);
            // note that we're translating the scene in the reverse direction of where we want to move
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
            
            glBindTexture(GL_TEXTURE_2D, tex);
            
            glUseProgram(program);
            
            int modelLoc = glGetUniformLocation(program, "model");
            int viewLoc = glGetUniformLocation(program, "view");
            int projLoc = glGetUniformLocation(program, "projection");
//            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
            
            for(int i = 0; i < 2; i++) {
                x_off[i] += 0.0001f * x_dir[i];
                y_off[i] += 0.00007f * y_dir[i];
                
                if(x_off[i] > 0.5f || x_off[i] < -0.5f) {
                    x_dir[i] *= -1;
                }
                
                if(y_off[i] > 0.5f || y_off[i] < -0.5f) {
                    y_dir[i] *= -1;
                }
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x_off[i], y_off[i], -1.0f)); 
                model = glm::rotate(model, (float) glfwGetTime() * glm::radians((i + 1) * 60.f), glm::vec3(0.5f, 1.f, 0.f));
                
                model = glm::translate(model, glm::vec3(x_off[i], y_off[i], -1.0f)); 
                
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
                
                glBindVertexArray(vao);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }
            
            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
        
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return;
    }

};

#endif // CAMERAEXAMPLE_HPP
