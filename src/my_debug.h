#ifndef DEBUG_H
#define DEBUG_H

// #define debug_all
// #define debug_flow

// #define debug_mouse
#define debug_shaders

void check_error();

// #define check_error() ( << "ERROR: " (glGetError()) << "\n")
#define check_error_prefixed(prefix) (std::cout << prefix; check_error())

#endif /* DEBUG_H */