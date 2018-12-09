#version 330 core

out vec4 FragColor;
in vec3 TexCoords;

uniform samplerCube textureskybox;



void main()
{

vec3 result_SkyboxTexture = texture(textureskybox, TexCoords).xyz;

FragColor = vec4(result_SkyboxTexture,1.0f);

}