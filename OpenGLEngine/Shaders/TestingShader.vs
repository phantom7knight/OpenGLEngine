#version 330 core

layout(location = 0) in vec3 cube_vert;
layout(location = 1) in vec3 cube_normal;
layout(location = 2) in vec3 cube_color;

uniform vec4 Color_Send;
uniform mat4 MVP_matrix;
uniform mat4 modelmat;


uniform vec3 eyepos;
uniform vec3 lightpos;

out vec4 vertcolor;
out vec3 FragPos;
out vec3 aNormal;

out vec3 aeyepos;
out vec3 alightpos;

void main()
{

	aeyepos = eyepos;
	alightpos = lightpos;
	FragPos = vec3(modelmat * vec4(cube_vert,1.0));
	aNormal = mat3(transpose(inverse(modelmat))) * cube_normal;
	vertcolor = Color_Send;//(vec4(cube_color,1.0));
	gl_Position = MVP_matrix * vec4(cube_vert,1.0);

}



