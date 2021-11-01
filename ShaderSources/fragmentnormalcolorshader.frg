#version 450 core

in VS_OUT {
    vec3 N;
    vec3 L;
    vec3 V;
} fs_in;

in vec3 fragpos;
in vec3 Color;

uniform vec3 lightcolor;
uniform vec3 lightpos;
uniform vec4 triangleColor;

uniform vec3 diffuse_albedo = vec3(0.5,0.2,0.7);
uniform vec3 specular_albedo = vec3(0.9);
uniform float specular_power = 128.0;

out vec4 FragColor;


void main(void) {

    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    vec3 R = reflect(-L,N);

    vec3 diffuse = max(dot(N,L),0.0) * diffuse_albedo;
    vec3 specular = pow(max(dot(R,V),0.0), specular_power) * specular_albedo;

    FragColor = vec4(diffuse + specular, 1.0) * triangleColor * vec4(Color,1.0);

}
