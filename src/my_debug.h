#ifndef MY_DEBUG_H
#define MY_DEBUG_H

#include <iostream>

// #define debug_all
// #define debug_flow

// #define debug_mouse
#define debug_shaders

// void check_error();
void gl_sane_error();

#define check_error() ( std::cout << "ERROR: " << gl_sane_error() << "\n")
#define check_error_prefixed(prefix) std::cout << prefix; check_error()

#endif /* MY_DEBUG_H */