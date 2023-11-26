

#ifndef ABSTRACT_SIMULATION_H
#define ABSTRACT_SIMULATION_H


#include <chrono>
#include <unordered_map>

#include "Window.h"
#include "Terminal.h"

#include "glad/glad.h"
#include "glfw3.h"
#include "glm.hpp"


class AbstractSimulation {
public:

    //Window information
    Window window;
    Terminal terminal;
    //Camera camera;
    int width;
    int height;
    
    //Scaling factors
    float scale_factor;
    float x_scale;
    float y_scale;
    GLfloat scale[4];

    void init_window();
    
    void check_window();
    
    virtual void run()=0;
    
    AbstractSimulation();
    virtual ~AbstractSimulation();

    void log(const char* text);
    void log(std::string text);

    void handleKeyboardInput();

    std::unordered_map<int, int> m_keyStates;
};

#endif /* ABSTRACT_SIMULATION_H */