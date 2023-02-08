#version 330 core

// Ouput data
out vec4 color;
in vec2 o_uv0;
uniform sampler2D colorText;


void main(){

        color =texture(colorText,o_uv0);
        // color =vec4(o_uv0,0,1);

}
