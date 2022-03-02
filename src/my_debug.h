

#ifndef DEBUG_H
#define DEBUG_H

// #define debug_all
// #define debug_flow

// #define debug_mouse
#define debug_shaders

#define check_error() (std::cout << "ERROR: " << glGetError() << "\n")
#define check_error_prefixed(prefix) (std::cout << prefix << "ERROR: " << glGetError() << "\n")

#endif /* DEBUG_H */