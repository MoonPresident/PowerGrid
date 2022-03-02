#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec3 aOffset;
uniform vec4 colorIn;
out vec4 color;
  
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos + aOffset, 1.0);
    color = colorIn;
}