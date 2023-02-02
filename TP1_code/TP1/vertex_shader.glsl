#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projM;

//TODO create uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.

void main(){

        // TODO : Output position of the vertex, in clip space : MVP * position
        gl_Position =   projM*viewM*modelM*vec4(vertices_position_modelspace,1);

}

