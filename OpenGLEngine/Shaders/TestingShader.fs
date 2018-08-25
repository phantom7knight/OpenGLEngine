#version 330 core

in vec4 vertcolor;
out vec4 fragColor;

in vec3 aNormal;
in vec3 FragPos;
in vec3 aeyepos;
in vec3 alightpos;

void main()
{

//=============================================================================================
//Light Calculations
//=============================================================================================
	//Ambient Lighting
	float ambient_strength = 1.0;
	vec4 lite_color = vec4(1.0,1.0,0.0,1.0);
	vec4 ambient = ambient_strength * lite_color;
	
	//Diffuse Lighting
	vec3 norm = normalize(aNormal);
	vec3 lightdir = normalize(alightpos - FragPos);
	float diff = max(dot(norm,lightdir),0.0);
	vec4 diffuse = diff * vec4(1,1,1,1);

	//Specular Lighting
	float specular_strength = 1.0;
	vec3 viewdir = normalize(aeyepos - FragPos);
	vec3 reflectdir = reflect(-lightdir,norm);
	float spec = pow(max(dot(viewdir,reflectdir),0.0),128);
	vec4 Specular = specular_strength * spec * vec4(1,1,1,1);

	vec4 Light_res =  (ambient + diffuse + Specular) * vertcolor;//vec4(1,0.5,0.31,1.0);
//=============================================================================================




	//Temprary
	vec4 colo_temp = vec4(noise2(FragPos.xy * 0.5),0.0,1.0)+Light_res;	//Noise returns random value between [-1,1]


	fragColor  = colo_temp;//res;
	//fragColor = vec4(aNormal,1.0);
}

