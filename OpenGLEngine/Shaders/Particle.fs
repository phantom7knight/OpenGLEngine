#version 430

uniform vec4 ParticleColor;
uniform sampler2D ParticleTex;

out vec4 FragColor;

void main()
{
	
	//vec4 mixedvalue = mix(ParticleColor,vec4(1),0.05f);
	
	vec4 particleColor = vec4(15.0f,5.0f,0.0f,1.0f);
	
    FragColor = particleColor;// vec4(texture(ParticleTex,gl_PointCoord) * ParticleColor);//ParticleColor;//vec4(1,0,1,1);//vec4(texture(ParticleTex,gl_PointCoord) * ParticleColor);
}