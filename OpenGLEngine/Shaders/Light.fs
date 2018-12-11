#version 330 core

out vec4 fragColor;

in vec3 Normals;
in vec3 Fragpos;
in vec2 TexCoords;


uniform vec3	objectCol;

uniform vec3	cameraPos;


uniform vec3	lightPos;
uniform float 	Lightintensity;


//Smapler Texture

uniform sampler2D reflectionUp;
uniform sampler2D reflectionDown;

int lightMode = 1;


vec3 CalculateDirectionalLight()
{
	if(lightMode == 0)
	{
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;

				
		//Ambient Color
		vec3 ambientColor = vec3(1.0f,1.0f,1.0f);
		float ambientStrength = 0.5;
		ambient = ambientStrength * ambientColor ;

		//Diffuse 
		vec3 lightdir = normalize(lightPos - Fragpos);
		vec3 norm = normalize(Normals);
		float diff = max(dot(norm,lightdir),0.0);
		diffuse = diff * (objectCol);

		//Specular
		float specularStrength = 1.0f;
		float specularIntensity = 16;
		vec3 viewdir = normalize(cameraPos - Fragpos);	
		vec3 reflectdir = reflect(-lightdir,norm);
		float spec = pow(max(dot(viewdir,reflectdir),0.0),specularIntensity);
		specular = specularStrength * spec * (objectCol);
	 
		return ( ambient );//+ diffuse + specular */
	}
	
	else if(lightMode == 1)
	{

		vec3 	kd 		= vec3(0.7,0.7,0.7);//strmaterial.diffuse;
		vec3 	ks 		= vec3(0.5,0.5,0.5);//strmaterial.specular;
		float   alpha 	= 2;
		
		//vec3 lightdir = vec3(0.0,100.0,-400.0);
		
		vec3 L = normalize(lightPos - Fragpos);			//(lightPos - Fragpos);
		vec3 V = normalize(cameraPos - Fragpos);
		vec3 N = normalize(Normals);
		N = abs(N);

		vec3 R = 2 * dot(V,N) * N - V;

		vec3 reflectionCoords = R / length(R);
		vec3 reflection;

		if(reflectionCoords.z < 0)
		{
			
			vec2 accessReflectionCoords = vec2((reflectionCoords.x / (1 - reflectionCoords.z)) * 0.5 + 0.5 , (reflectionCoords.y / (1 - reflectionCoords.z)) * 0.5 + 0.5);
			reflection = texture(reflectionDown,accessReflectionCoords).xyz;
		}
		else
		{
			vec2 accessReflectionCoords = vec2((reflectionCoords.x / (1 + reflectionCoords.z)) * 0.5 + 0.5 , 	(reflectionCoords.y / (1 + reflectionCoords.z)) * 0.5 + 0.5);
			reflection = texture(reflectionDown,accessReflectionCoords).xyz;
		}

		
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
		
		vec3 final_BRDF = (Ia * kd + I * BRDF * (LN)) * Lightintensity + reflection.xyz;
		
		return final_BRDF * objectCol;


	}

}

void main()
{
	
	vec3 result_Dir = CalculateDirectionalLight();
	
	fragColor = vec4(result_Dir,1.0);

	//fragColor = vec4(texture(reflectionUp,TexCoords).xyz,1.0);

		
}
