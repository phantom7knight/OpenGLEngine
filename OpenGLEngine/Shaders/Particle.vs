#version 430

in vec3 aPos;
layout( location = 1 ) in vec2 aTexCoords;

uniform mat4 ViewMatrix;
uniform mat4 ProjMatrix;

out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;
    gl_Position = ProjMatrix*ViewMatrix*vec4(aPos,1.0);
} 