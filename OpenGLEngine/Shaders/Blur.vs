#version 330 core

layout(location = 0) in vec3 cords;
layout(location = 1) in vec2 texturecoords;


uniform mat4 modelmat;
uniform mat4 viewmat;
uniform mat4 projectionmat;

out vec2 TexCoords;

void main()
{

	TexCoords = texturecoords;

	
	gl_Position =  vec4(cords,1.0f); //projectionmat * viewmat * modelmat * 

}
