#version 330 core

layout(location = 0) in vec3 light_cords;
layout(location = 1) in vec3 light_normals;
layout(location = 2) in vec3 light_color;

//uniform mat4 worldmat;
uniform vec4 Color_Send;
uniform mat4 modelmat;
uniform vec3 eyepos;
uniform vec3 lightpos;

out vec4 vertcolor;
out vec3 vertnormal;
out vec3 lightvec,eyevec;


void main()
{
	vertnormal = mat3(transpose(inverse(modelmat))) * light_normals;
	lightvec = lightpos;
	eyevec = eyepos;

	gl_Position = modelmat * vec4(light_cords,1.0);
	vertnormal = light_normals;
	vertcolor = (Color_Send);

}
