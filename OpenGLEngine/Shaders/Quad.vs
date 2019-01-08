#version 430 core

layout(location = 0) in vec3 cords;
layout(location = 1) in vec2 texturecoords;


uniform mat4 modelmat;
uniform mat4 viewmat;
uniform mat4 projectionmat;

out vec2 TexCoords;
out vec3 Fragpos;

void main()
{

	TexCoords = texturecoords;

	Fragpos = vec3(modelmat * vec4(cords,1.0));

	
	gl_Position = projectionmat * viewmat * modelmat * vec4(cords,1.0f);

}
