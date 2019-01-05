#version 430 core

layout(location = 0) in vec3 light_cords;
layout(location = 1) in vec3 light_normals;
layout(location = 2) in vec2 light_texture;

uniform mat4 modelmat;
uniform mat4 viewmat;
uniform mat4 projectionmat;


out vec3 Fragpos;
out vec3 Normals;
out vec2 TexCoords;



void main()
{

	TexCoords = light_texture;

	Fragpos = vec3(modelmat * vec4(light_cords,1.0));
	
	Normals = mat3(transpose(inverse(modelmat))) * light_normals;
	
	gl_Position = projectionmat * viewmat * modelmat * vec4(light_cords,1.0f);

}
