#version 450 core

layout(binding=0) uniform sampler2D texture1;
layout(binding=1) uniform sampler2D texture2;

in VS_OUT{
   vec4 color;
   vec2 TexCoord;
} fs_in;

uniform vec4 triangleColor;
out vec4 FragColor;

void main(void) {
   vec4 outcolor = mix(texture(texture1, fs_in.TexCoord), texture(texture2, fs_in.TexCoord), 0.5);
   vec4 mixcolor = mix(outcolor, triangleColor,0.5 );
   FragColor = mixcolor;
}
