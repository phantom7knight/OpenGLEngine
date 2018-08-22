#version 330 core

in vec4 vertcolor;

in vec3 vertnormal;
in vec3 lightvec;
in vec3 eyevec;

out vec4 fragColor;

vec3 kd = vec3(0.0,1.0,0.0);
vec3 ks= vec3(0.0,1.0,0.0);
float shininess_alpha;




void main()
{

	vec3 N = normalize(vertnormal);
	vec3 L = normalize(lightvec);

	fragColor = vertcolor;

}
