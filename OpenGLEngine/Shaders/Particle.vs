#version 430

in vec3 Pos;

void main()
{
    gl_Position = vec4(Pos,1.0);
} 