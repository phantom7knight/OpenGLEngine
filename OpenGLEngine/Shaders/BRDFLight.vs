#version 330 core

layout(location = 0) in vec3 source_cords;

uniform mat4 MVP_mat;

out vec4 vertcolor;

void main()
{

	vecertcolor = MVP_mat * vec4(source_cords,1.0);
}
