#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projM;

out vec2 o_uv0;


//TODO create uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.

void main(){

        o_uv0=vec2(vertices_position_modelspace[0],vertices_position_modelspace[2]);
        // TODO : Output position of the vertex, in clip space : MVP * position
        gl_Position =   projM*viewM*modelM*vec4(vertices_position_modelspace,1);

}

