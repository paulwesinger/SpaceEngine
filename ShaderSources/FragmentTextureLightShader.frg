#version 450 core

layout(binding=0) uniform sampler2D texture1;
layout(binding=1) uniform sampler2D texture2;

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

//uniform sampler2D floorTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool blinn;
uniform vec4 triangleColor;
uniform int useTexture_2;
uniform bool hasTexture;

void main()
{           
    vec3 color;
    if (hasTexture) {

        if (useTexture_2 == 0)
            color = texture(texture1,fs_in.TexCoords).rgb;     //(floorTexture, fs_in.TexCoords);
        else
            color = mix(texture(texture1, fs_in.TexCoords), texture(texture2, fs_in.TexCoords), 0.8).rgb;
    }
    else
    {
        color = triangleColor.rgb;
    }

        // ambient
        vec3 ambient = 0.5 * color;
        // diffuse
        vec3 lightDir = normalize(lightPos - fs_in.FragPos);
        vec3 normal = normalize(fs_in.Normal);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = diff * color;
        // specular
        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = 0.0;
        if(blinn)
        {
            vec3 halfwayDir = normalize(lightDir + viewDir);
            spec = pow(max(dot(normal, halfwayDir), 0.0), 1.0);
        }
        else
        {
            vec3 reflectDir = reflect(-lightDir, normal);
            spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
        }

        vec3 specular = vec3(1.0) * spec; // assuming bright white light color

        FragColor = vec4(ambient + diffuse + specular,1.0 ) * triangleColor;
}
