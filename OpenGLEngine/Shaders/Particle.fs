#version 430

uniform vec4 ParticleColor;
uniform sampler2D ParticleTex;

out vec4 FragColor;

void main()
{
	
	
	
    FragColor = vec4(texture(ParticleTex,gl_PointCoord) * ParticleColor);//ParticleColor;//vec4(1,0,1,1);//vec4(texture(ParticleTex,gl_PointCoord) * ParticleColor);
}