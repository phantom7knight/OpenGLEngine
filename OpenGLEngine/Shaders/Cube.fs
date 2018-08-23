#version 330 core

in vec4 vertcolor;
out vec4 fragColor;

in vec3 aNormal;
in vec3 FragPos;
in vec3 aeyepos;
in vec3 alightpos;

void main()
{
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
	float specular_strength = 0.5;
	vec3 viewdir = normalize(aeyepos - FragPos);
	vec3 reflectdir = reflect(-lightdir,norm);
	float spec = pow(max(dot(viewdir,reflectdir),0.0),32);
	vec4 Specular = specular_strength * spec * vec4(1,1,1,1);

	vec4 res =  (ambient + diffuse + Specular) * vertcolor;//vec4(1,0.5,0.31,1.0);
	//fragColor = vec4(aNormal,1.0);
	fragColor  = res;
}

