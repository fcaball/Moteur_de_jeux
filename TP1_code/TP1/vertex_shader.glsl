#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec2 uv;
// layout(location = 2) in vec2 height;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projM;

// uniform ivec2 HALF_TERRAIN_SIZE;
uniform sampler2D heightMapTexture;
// uniform float scale;
// uniform float half_scale;

out vec2 o_uv0;


//TODO create uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.

void main(){

        o_uv0=uv;

        float height = texture(heightMapTexture, vertices_position_modelspace.xz).r /* - half_scale */;
        vec2 pos  = (vertices_position_modelspace.xz*2.0-1)/* *HALF_TERRAIN_SIZE */;
        gl_Position =  projM*viewM*modelM*vec4(pos.x, height, pos.y, 1);
        // vec3 poswithheight=vec3(vertices_position_modelspace[0],height,vertices_position_modelspace[2]);
        // TODO : Output position of the vertex, in clip space : MVP * position
        // gl_Position =   projM*viewM*modelM*vec4(poswithheight,1);
        // gl_Position =   projM*viewM*modelM*vec4(vertices_position_modelspace,1);

}

