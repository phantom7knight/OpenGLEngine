#version 330 core

layout(location = 0) in vec3 cube_vert;
//layout(location = 1) in vec3 cube_color;

uniform vec4 Color_Send;	
uniform mat4 MVP_matrix;

out vec4 vertColor;

void main()
{

	gl_Position = MVP_matrix * vec4(cube_vert,1.0);
	vertColor = Color_Send;

}