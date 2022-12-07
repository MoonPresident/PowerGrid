#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec4 colorIn;

out vec4 color;

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = colorIn;
}

//Links to simple_colorable.fs