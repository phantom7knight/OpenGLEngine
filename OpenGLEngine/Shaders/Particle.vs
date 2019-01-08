#version 430

in vec3 Positions;

void main()
{
    gl_Position = vec4(Positions,1.0);
}