
#include "AbstractSimulation.h"

AbstractSimulation::AbstractSimulation(): terminal() {}

AbstractSimulation::~AbstractSimulation() {}

void AbstractSimulation::init_window() {
    //Set window and scale.
    
    glfwGetFramebufferSize(window.getWindow(), &width, &height);
    glViewport(0, 0, width, height);
    scale_factor = 1.f;
    x_scale = scale_factor * ((width != height) * (float) height / (float) width + (width == height));
    y_scale = scale_factor;

    
};

void AbstractSimulation::check_window() {
    int prev_width = width;
    int prev_height = height;
    glfwGetFramebufferSize(window.getWindow(), &width, &height);
    
    if(prev_width == width && prev_height == height) {
        return;
    }

    terminal.text.setPerspective(width, height);
    
    glViewport(0, 0, width, height);
    x_scale = scale_factor * ((width != height) * (float) height / (float) width + (width == height));
    y_scale = scale_factor;
};

void AbstractSimulation::log(const char* text) {
    terminal.log(text);
    // system.log();
}

void AbstractSimulation::log(std::string text) {
    log(text.c_str());
}