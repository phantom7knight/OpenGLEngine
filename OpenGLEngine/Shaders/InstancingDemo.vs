#version 330 core
layout(location = 0) in vec2 vertex_cord;

//uniform vec3 MVP_matrix;
uniform vec2 offsets[100];

out vec4 vertcolor;

void main()
{
	vec2 offset = offsets[gl_InstanceID];
	gl_Position =  vec4(vetex_cord + offset,0.0,1.0);
	vertcolor = vec4(0.2,0.2,0.2,1.0);


}