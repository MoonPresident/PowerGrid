



#ifndef SHADERS_H
#define SHADERS_H

#include "main.h"

struct Shader {
    GLuint shader;
    static const char** shader_source;
};

// Source code for vertex shader
static const char* vertex_shader_source[] = {
    "#version 450 core                                  \n"
    "                                                   \n"
    "void main(void) {                                  \n"
    "   // Declare a hard-coded array of positions      \n"
    "   const vec4 vertices[3] = vec4[3](               \n"
    "           vec4(0.25, -0.25, 0.5, 1.0),            \n"
    "           vec4(-0.25, -0.25, 0.5, 1.0),           \n"
    "           vec4(0.25, 0.25, 0.5, 1.0));            \n"
    "                                                   \n"
    "   // Index into our array using gl_VertexID       \n"
    "                                                   \n"
    "   gl_Position = vertices[gl_VertexID];            \n"
    "}                                                  \n"
};

// Source code for fragment shader
static const char* fragment_shader_source[] = {
    "#version 450 core                                  \n"
    "                                                   \n"
    "out vec4 color;                                    \n"
    "                                                   \n"
    "void main(void)                                    \n"
    "{                                                  \n"
    "   color = vec4(0.0, 0.8, 1.0, 1.0);               \n"
    "}                                                  \n"
};

static const char* offset_shader_source[] = {
    "#version 450 core                                  \n"
    "                                                   \n"
    "// 'offset' is an input vertex attribute           \n"
    "layout (location = 0) in vec4 offset;              \n"
    "                                                   \n"
    "void main(void)                                    \n"
    "{                                                  \n"
    "   const vec4 vertices[3] = vec4[3](               \n"
    "           vec4(0.25, -0.25, 0.5, 1.0),            \n"
    "           vec4(-0.25, -0.25, 0.5, 1.0),           \n"
    "           vec4(0.25, 0.25, 0.5, 1.0)             \n"
    "   );                                              \n"
    "                                                   \n"
    "   //Add 'offset' to our hard-coded vertex         \n"
    "   gl_Position = vertices[gl_VertexID] + offset;   \n"
    "}                                                  \n"
    
};


#endif /* SHADERS_H */