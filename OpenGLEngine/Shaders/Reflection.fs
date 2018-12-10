#version 330 core



in vec2 TexCoords;
in vec3 Normals;
in vec3 Fragpos;
in vec3 center_reflection;

out FragColor;

int lightMode = 1;


uniform vec3 lightPos;
uniform float Lightintensity;
uniform vec3 objectCol;


vec3 CalculateDirectionalLight()
{

	vec3 	kd 		= vec3(0.7,0.7,0.7);//strmaterial.diffuse;
	vec3 	ks 		= vec3(0.5,0.5,0.5);//strmaterial.specular;
	float   alpha 	= 2;
	
	//vec3 lightdir = vec3(0.0,100.0,-400.0);
	
	vec3 L = normalize(lightPos - Fragpos);			 //(lightPos - Fragpos);
	vec3 V = normalize(center_reflection - Fragpos); //cameraPos
	vec3 N = normalize(Normals);
	N = abs(N);
	
	vec3 	H 		= 	normalize(L + V);
	float 	LN 		=	max(dot(N,L),0.0); 
	float 	HN 		=	max(dot(H,N),0.0); 
	
	//objectCol *= texture(AlbedoTexture,TexCoord + 50 + 50).xyz;
	
	vec3 I  = vec3(1.0f,1.0f,1.0f);	//Light 	Color
	vec3 Ia = vec3(0.5f,0.5f,0.5f);	//Ambient 	Color
	
	vec3 FresnelTerm = ks + (vec3(1.0,1.0,1.0) - ks) * (pow((1-dot(L,H)),5));
	
	float Gterm = 1 / pow(dot(L,H),2);
	
	float DTerm = ((alpha + 2) / (2*3.14)) * pow(dot(N,H),alpha);
	
	
	
	vec3 BRDF  = kd/3.14 + ( DTerm * Gterm * FresnelTerm) / 4;
	
	vec3 final_BRDF = (Ia * kd + I * BRDF * (LN)) * Lightintensity;
	
	return final_BRDF * objectCol;


}


void main()
{
	
	vec3 result_Dir = CalculateDirectionalLight();

	FragColor = vec4(result_Dir,1.0);
		
}
