#version 430

in vec3 aPos;

uniform mat4 ViewMatrix;
uniform mat4 ProjMatrix;

out vec2 TexCoords;

void main()
{
    gl_Position = ProjMatrix*ViewMatrix*vec4(aPos,1.0);
} 