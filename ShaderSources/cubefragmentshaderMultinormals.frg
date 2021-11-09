#version 450 core

layout(binding=0) uniform sampler2D texture1;
layout(binding=1) uniform sampler2D texture2;

out vec4 FragColor;


in VS_OUT {
    vec3 N;
    vec3 L;
    vec3 V;
} fs_in;

in vec3 normal_out;
in vec3 fragpos;
in vec2 TexCoord;

uniform vec3 lightcolor;
uniform vec3 lightpos;
uniform vec4 triangleColor;

uniform vec3 diffuse_albedo = vec3(0.5,1.0,0.7); //vec3(0.5,0.2,0.7);
uniform vec3 specular_albedo = vec3(0.8);
uniform float specular_power = 255.0;



void main(void) {

    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

/*   pointlight
    vec3 R = reflect(-L,N);

    vec3 diffuse = max(dot(N,L),0.0) * specular_albedo;
    vec3 specular = pow(max(dot(R,V),0.0), specular_power) * specular_albedo;


    vec4 texcolor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.8);
    FragColor = vec4(diffuse + specular, 1.0) * texcolor * triangleColor;
*/


// Ambientes licht
   float ambientStrength = 1.0;
   vec3 ambient = lightcolor * ambientStrength;

   // Bis hierher passt

   vec3 norm =  normalize(normal_out);
   vec3 lightDir = normalize(lightpos - fragpos);

   float diff = max(dot(normal_out,lightDir),0.0);
   vec3 diffuse = diff * lightcolor;

    vec4 texcolor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.8);
    FragColor = texcolor * (vec4(diffuse,1.0) + vec4(ambient,1.0));

}
