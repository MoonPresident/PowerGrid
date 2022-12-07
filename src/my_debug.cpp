#include "my_debug.h"
#include "callbacks.h"
// GL_NO_ERROR 	                        0 	    No user error reported since the last call to glGetError.
// GL_INVALID_ENUM 	                    1280 	Set when an enumeration parameter is not legal.
// GL_INVALID_VALUE 	                1281 	Set when a value parameter is not legal.
// GL_INVALID_OPERATION 	            1282 	Set when the state for a command is not legal for its given parameters.
// GL_STACK_OVERFLOW 	                1283 	Set when a stack pushing operation causes a stack overflow.
// GL_STACK_UNDERFLOW 	                1284 	Set when a stack popping operation occurs while the stack is at its lowest point.
// GL_OUT_OF_MEMORY 	                1285 	Set when a memory allocation operation cannot allocate (enough) memory.
// GL_INVALID_FRAMEBUFFER_OPERATION 	1286 	Set when reading or writing to a framebuffer that is not complete.

void check_error() {
    switch(glGetError()) {
    case 0:         std::cout << "GL_NO_ERROR\n";
    case 1280:      std::cout << "GL_INVALID_ENUM\n";
    case 1281:      std::cout << "GL_INVALID_VALUE\n";
    case 1282:      std::cout << "GL_INVALID_OPERATION\n";
    case 1283:      std::cout << "GL_STACK_OVERFLOW\n";
    case 1284:      std::cout << "GL_STACK_UNDERFLOW\n";
    case 1285:      std::cout << "GL_OUT_OF_MEMORY\n";
    case 1286:      std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
    default:        std::cout << "GL_NO_ERROR\n";
    }
}