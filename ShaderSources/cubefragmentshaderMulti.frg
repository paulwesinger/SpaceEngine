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
   //vec4 outcolor = mix(texture(texture1, fs_in.TexCoord), texture(texture2, fs_in.TexCoord), 0.5);
   //vec4 mixcolor = mix(outcolor, triangleColor,0.2 );
   //outcolor.a = 0.7;
   //FragColor = outcolor;

    vec4 texel = texture(texture2, fs_in.TexCoord);
    vec4 sampled = texel * triangleColor;
    sampled.a = triangleColor.a;
    FragColor = sampled;
}




/*


static const GLchar * vs2D_src = {
    "#version 440 core                                              \n"
    "layout (location = 0) in vec2 vertex;                          \n"
    "layout (location = 1) in vec2 tex;                             \n"

    "uniform mat4 projection;                                       \n"
    "out VS_OUT {                                                   \n"
    "   vec2 uv;                                                    \n"
    "} vs_out;                                                      \n"

    "void main()                                                    \n"
    "{                                                              \n"
    "   gl_Position = projection * vec4(vertex,0.0,1.0);            \n"
    "   vs_out.uv =  tex;                                           \n"
   "}                                                               \n"
};

static const GLchar * fs2D_src = {
    "#version 440 core                                              \n"

    "in VS_OUT {                                                    \n"
    "   vec2 uv;                                                    \n"
    "} fs_in;                                                       \n"

    "out vec4 fragcolor;                                            \n"
    "uniform sampler2D text;                                        \n"
    "uniform vec4 col2D;                                            \n"

    "void main()                                                    \n"
    "{                                                              \n"
    "   vec4 texel = texture(text,fs_in.uv);                        \n"
    "   if(texel.r == 0.0 && texel.g == 0.0 && texel.b == 0)        \n"
    "       discard;                                                \n"
    "   else {                                                      \n"
    "       vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, fs_in.uv).r); \n"
    "       fragcolor =    sampled * col2D;                         \n"
    "   }                                                           \n"
    "}                                                                "
};
*/
