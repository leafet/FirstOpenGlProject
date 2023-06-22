#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 position;

uniform float xOffset;
uniform float yOffset;

void main()
{
    gl_Position = vec4(position.x + xOffset, position.y + yOffset, position.z, 1.0);
}