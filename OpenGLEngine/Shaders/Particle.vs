#version 430

in vec3 particlePos;

void main()
{
    gl_Position = vec4(particlePos,1.0);
}