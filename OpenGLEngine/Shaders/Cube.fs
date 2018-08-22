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


	vec4 res =  (ambient + diffuse) * vertcolor;//vec4(1,0.5,0.31,1.0);
	//fragColor = vec4(aNormal,1.0);//res;
	fragColor  = res;
}



//out vec4 outfragcolor;
//
//void main()
//{
//		outfragcolor = vertColor;//vec4(1.0,0.0,0.0,1.0);//vertColor;
//}