#version 330 core
layout(location = 0) in vec2 vertex_cord;
layout(location = 1) in vec2 vertex_offset;


uniform mat4 MVP_matrix;

out vec4 vertcolor;

void main()
{
	gl_Position =  MVP_matrix * vec4(vertex_cord + vertex_offset ,0.0,1.0);
	vertcolor = vec4(1.0,1.0,1.0,1.0);

}