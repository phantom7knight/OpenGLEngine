#version 430

uniform vec4 ParticleColor;
uniform sampler2D ParticleTex;

out vec4 FragColor;

float exposure = 1.0f;
float gamma = 2.2f;
void main()
{
	
	//vec4 mixedvalue = mix(ParticleColor,vec4(1),0.05f);
	
	//Tone Mapping
	vec4 res = vec4(1.0f) - exp(-ParticleColor * exposure);
    
	//Final Result and Gamma Corrections
	vec4 finalGammaCorrected = pow(res,vec4(1.0f/gamma));
	FragColor = finalGammaCorrected;// vec4(texture(ParticleTex,gl_PointCoord) * ParticleColor);//ParticleColor;//vec4(1,0,1,1);//vec4(texture(ParticleTex,gl_PointCoord) * ParticleColor);
}