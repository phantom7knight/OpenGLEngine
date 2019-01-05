#version 430 core

in vec2 TexCoords;
in vec3 Fragpos;
in vec3 Normals;

out vec4 FragColor;

//uniform sampler2D reflectionUp;
//uniform sampler2D reflectionDown;

uniform sampler2D gPosition;
//uniform sampler2D gNormal;
//uniform sampler2D gAlbedoSpec;

void main()
{

    
    FragColor = vec4(texture(gPosition,TexCoords).xyz,1.0);
    //FragColor = vec4(texture(gNormal,TexCoords).xyz,1.0);
    //FragColor = vec4(texture(gAlbedoSpec,TexCoords).xyz,1.0);
    //FragColor = vec4(1.0,1.0,0.0,1.0);
}