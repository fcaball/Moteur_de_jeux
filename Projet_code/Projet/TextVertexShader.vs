#version 330 core

layout(location = 0) in vec2 vertexPosition_screenspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

void main()
{
    gl_Position = vec4(vertexPosition_screenspace, 0.0, 1.0);
    UV = vertexUV;
}
