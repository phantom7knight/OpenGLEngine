#version 330 core

#define PI 3.14


layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;


out vec4 fragColor;

in vec3 Normals;
in vec3 Fragpos;
in vec2 TexCoords;

//Object Properties
uniform vec3	objectCol;
uniform vec3	cameraPos;

//Light Properties
uniform vec3	lightPos;
uniform float 	Lightintensity;
int lightMode = 1;



//Relfection related
uniform int IsReflection;
uniform sampler2D reflectionUp;
uniform sampler2D reflectionDown;



//Bloom related
uniform int IsBloom;
vec3 threshold = vec3(0.2126,0.7152,0.0722);



//======================================================================
//Trowbridge Reitz Distribution GGX

float DistributionGGX(float alpha,vec3 N,vec3 H)
{
	float numerator = alpha * alpha;
	float NH = max(dot(N,H),0.0);
	float Aminus1 = (alpha * alpha) - 1;

	float denominator = PI * pow((NH * Aminus1 + 1),2);

	return (numerator / denominator);

}
//======================================================================



//======================================================================
//Schlick-Beckmann Geometry GGX
float GeometrySchlick(vec3 N , vec3 Direction , float Alpha)
{
	float NDirection = max(dot(N,Direction),0.0); 

	float denominator = (NDirection * (1 - Alpha)) + Alpha;

	return (NDirection / denominator);
}



//Smith Geometry method
float GeometrySmith(vec3 N, vec3 V,vec3 L, float Alpha)
{
	float ggx1 = GeometrySchlick(N,V,Alpha);
	float ggx2 = GeometrySchlick(N,L,Alpha);

	return ggx1 * ggx2;

}

//======================================================================


//======================================================================
//Fresnal Schlick
vec3 FresnalSchlick(float costheta , vec3 F0)
{
	// float HV = max(dot(H,V),0.0);

	// float A = pow((1 - HV),5);

	// return BaseReflectivity + (1 - BaseReflectivity) * A;

	return F0 + (1.0-F0) * pow(1.0-costheta,5.0);
}

//======================================================================



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
	
	else if(lightMode == 1)//Micro Facet BRDF Model
	{

		vec3 	kd 		= vec3(0.7,0.7,0.7);//strmaterial.diffuse;
		vec3 	ks 		= vec3(0.5,0.5,0.5);//strmaterial.specular;
		float   alpha 	= 2;
		
		//vec3 lightdir = vec3(0.0,100.0,-400.0);
		
		vec3 L = normalize(lightPos - Fragpos);			//(lightPos - Fragpos);
		vec3 V = normalize(cameraPos - Fragpos);
		vec3 N = normalize(Normals);
		N = abs(N);

		//=========================================================================
		//Reflection Calculations
		//=========================================================================
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

		//=========================================================================
		
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
		
		vec3 final_BRDF;

		if(IsReflection == 1)
		{
			final_BRDF = (Ia * kd + I * BRDF * (LN)) * Lightintensity + reflection.xyz;
		}
		else
		{
			if(IsBloom == 1)
			{
				final_BRDF = (Ia * kd + I * BRDF * (LN)) * Lightintensity;
				float brigtness = dot(final_BRDF,threshold);

				if(brigtness > 1)
				{
					BrightColor = vec4(1.0,0.0,0.0,1.0);//vec4(final_BRDF,1.0);
				}
				else
				{
					BrightColor = vec4(0.0,0.0,0.0,1.0);
				}

				FragColor = vec4(1.0,0.0,0.0,1.0);//vec4(final_BRDF * objectCol , 1.0f);
			}
			else
			{
				final_BRDF = (Ia * kd + I * BRDF * (LN)) * Lightintensity;	
			}
		}
		
		
		return final_BRDF * objectCol;


	}

	else if(lightMode == 2)//Cook Torrence BRDF Model
	{
		//Parameters
		float alpha;//Roughness
			
		vec3 L = normalize(lightPos - Fragpos);			//(lightPos - Fragpos);
		vec3 V = normalize(cameraPos - Fragpos);
		vec3 N = normalize(Normals);
		vec3 H = (L + V) / length(L + V);

		float metalness;
		vec3 F0 =  vec3(0.2);
		F0 = mix(F0,objectCol.rgb,metalness);

		//N = abs(N);


		//float D = DistributionGGX(alpha,Normals,H);
		//float G = GeometrySmith();
		//vec3  F = FresnalSchlick();
		


	}
}

void main()
{
	// BrightColor = vec4(0.0,0.0,0.0,1.0);
	// FragColor = vec4(1.0,0.0,0.0,1.0);
	
	// vec3 result_Dir = CalculateDirectionalLight();
	
	// if(IsBloom == 0)
	// {
	// 	fragColor = vec4(result_Dir,1.0);
	// }
//===========================================================================
//Bloom calculations
//===========================================================================

	vec3 	kd 		= vec3(0.7,0.7,0.7);//strmaterial.diffuse;
	vec3 	ks 		= vec3(0.5,0.5,0.5);//strmaterial.specular;
	float   alpha 	= 2;
	
	//vec3 lightdir = vec3(0.0,100.0,-400.0);
	
	vec3 L = normalize(lightPos - Fragpos);			//(lightPos - Fragpos);
	vec3 V = normalize(cameraPos - Fragpos);
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
	
	vec3 final_BRDF;
	
	final_BRDF = (Ia * kd + I * BRDF * (LN)) * Lightintensity;
	
	float brigtness = dot(final_BRDF,threshold);
	if(brigtness > 1)
	{
		BrightColor = vec4(final_BRDF,1.0);
	}
	else
	{
		BrightColor = vec4(0.0,0.0,0.0,1.0);
	}
	FragColor = vec4(final_BRDF * objectCol , 1.0f);

//===========================================================================




}
