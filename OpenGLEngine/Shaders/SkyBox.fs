#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube textureskybox;



void main()
{
	
	vec4 result_SkyboxTexture = texture(textureskybox, TexCoords);
	
	vec4 final_color = result_SkyboxTexture;

	FragColor = final_color; //yolo_test;
}