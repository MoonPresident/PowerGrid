
#include "AbstractSimulation.h"

AbstractSimulation::AbstractSimulation() {
}
AbstractSimulation::~AbstractSimulation() {
    //Nada.
}

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
    
//        if(prev_width == width && prev_height == height) {
//            return;
//        }
    
    glViewport(0, 0, width, height);
    x_scale = scale_factor * ((width != height) * (float) height / (float) width + (width == height));
    y_scale = scale_factor;
};