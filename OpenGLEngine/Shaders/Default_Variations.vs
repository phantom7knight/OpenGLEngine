#version 330 core

layout(location = 0) in vec3 triangle_vertices;
layout(location = 1) in vec2 TexCords;

out vec4 vertcolor;

uniform vec4 Color_Send;
uniform mat4 worldmat;

out vec2 cords_tex;

void main()
{
	gl_Position = worldmat*vec4(triangle_vertices,1.0);
	vertcolor = Color_Send;
	cords_tex = TexCords;
}