#version 330 core



in vec2 TexCoords;
in vec3 Fragpos;
in vec3 Normals;

out vec4 FragColor;

uniform sampler2D reflectionUp;
//uniform sampler2D reflectionDown;

void main()
{
    FragColor = vec4(texture(reflectionUp,TexCoords).xyz,1.0);
}