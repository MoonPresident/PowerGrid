

#ifndef DEBUG_H
#define DEBUG_H

//#define debug_all
#define debug_shaders
//#define main_code

#define check_error() (std::cout << "ERROR: " << glGetError() << std::endl)

#endif /* DEBUG_H */