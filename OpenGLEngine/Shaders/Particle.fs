#version 430 core

uniform vec4 ParticleColor;
uniform sampler2D ParticleTex;

out vec4 FragColor;

void main()
{
    FragColor = vec4(texture(ParticleTex,gl_PointCoord) * ParticleColor);
}