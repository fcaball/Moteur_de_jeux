#version 330 core

// Ouput data
out vec4 color;
in vec2 o_uv0;
// flat in int numText;

uniform sampler2D text;
in vec4 boundsAndheight;


void main(){

        // if(boundsAndheight[3]<boundsAndheight[1]){
        //         color =texture(grass,o_uv0);
        // }else if(boundsAndheight[3]<boundsAndheight[2]){
        //         color =texture(rock,o_uv0);
        // }else {
           color =texture(text,o_uv0);
        // }

}
