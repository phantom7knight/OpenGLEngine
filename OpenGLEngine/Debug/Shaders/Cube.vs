#version 330 core

layout(location = 0) in vec3 cube_vert;

uniform vec4 Color_Send;	
uniform mat4 worldmat;	

out vec4 vertColor;

void main()
{

	gl_Position =  vec4(cube_vert,1.0);
	vertColor = Color_Send;

}