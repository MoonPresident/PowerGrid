

#ifndef CAMERA_H
#define CAMERA_H

//GLM library
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Camera {
public:
    //3D code.
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    glm::vec3 cameraPos;
    glm::vec3 cameraTarget;
    glm::vec3 cameraDirection;
    glm::vec3 up;
    glm::vec3 cameraRight;
    glm::vec3 cameraUp;
    glm::vec3 cameraFront;
    
    Camera () {
        projection = glm::perspective(
            glm::radians(45.0f), 
            1.3f, 
            0.1f, 
            100.f
        );
        
        view = glm::mat4(1.f);
        view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
        
        model = glm::mat4(1.0);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.f, 0.f, 0.f));
        
        //Camera
        cameraPos = glm::vec3(0.f, 0.f, 3.f);
        cameraTarget = glm::vec3(0.f, 0.f, 0.f);
        cameraDirection = glm::normalize(cameraPos - cameraTarget);
        up = glm::vec3(0.f, 1.f, 0.f);
        cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        cameraUp = glm::cross(cameraDirection, cameraRight);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    }
};

#endif /* CAMERA_H */