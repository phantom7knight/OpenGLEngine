#version 330 core

layout(location = 0) in vec3 triangle_vertices;
out vec4 vertcolor;
uniform vec4 Color_Send;

void main()
{
	gl_Position = vec4(triangle_vertices,1.0);
	vertcolor = Color_Send;
}