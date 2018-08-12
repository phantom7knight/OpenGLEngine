#version 330 core

layout(location = 0) in vec3 light_cords;
layout(location = 1) in vec3 light_normals;
layout(location = 2) in vec3 light_color;

uniform mat4 modelmat;

out vec4 vertcolor;

void main()
{

	gl_Position = modelmat * vec4(light_cords,1.0);
	vertcolor = vec4(light_color,1.0);
}
