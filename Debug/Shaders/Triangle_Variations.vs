#version 330 core

layout(locations = 0) in vec3 triangle_vertices;
out vec4 vertcolor;

int main()
{
	gl_Position = vec4(triangle_vertices,1.0);
	vertcolor = vec4(0.0,0.0,0.8,1.0);
}