#version 330 core

layout(location = 0) in vec3 light_cords;
layout(location = 1) in vec3 light_normals;
layout(location = 2) in vec3 light_color;

uniform mat4 modelmat;
uniform vec4 Color_send;


out vec3 Normals;
out vec4 vertcolor;


void main()
{

	
	gl_Position = modelmat * vec4(light_cords,1.0);
	Normals = mat3(transpose(inverse(modelmat))) * light_normals;
	vertcolor = (Color_send);

}
