#version 330 core

out vec4 fragColor;

in vec3 objectColor;
in vec3 Normals;
in vec3 Fragpos;
in vec4 vert_position;
in vec4 viewSpace;



uniform vec3 cameraPos;
uniform vec3 lightPos;

uniform float DeltaTime;

uniform vec3 fogColor;




vec3 CalculateDirectionalLight(Material strmaterial)
{
    
	if(lightMode == 0)		//Phong Model
	{
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
	
		//Normalize Object Color
		//vec3 objectColor = normalize(strmaterial.objectCol);
	
		//Ambient Color
		ambientColor = vec3(1.0f,1.0f,1.0f);
		float ambientStrength = 0.5;
		ambient = ambientStrength * ambientColor * strmaterial.objectCol;
	
		//Diffuse 
		vec3 lightdir = normalize(lightPos - Fragpos);
		vec3 norm = normalize(Normals);
		float diff = max(dot(norm,lightdir),0.0);
		diffuse = diff * strmaterial.objectCol;
	
		//Specular
		float specularStrength = 1.0f;
		float specularIntensity = 256;
		vec3 viewdir = normalize(cameraPos - Fragpos);
		vec3 reflectdir = reflect(-lightdir,norm);
		float spec = pow(max(dot(viewdir,reflectdir),0.0),specularIntensity);
		specular = specularStrength * spec * strmaterial.objectCol;
	
		return (specular + ambient + diffuse);
	}



void main()
{
	vec3 result_Dir = CalculateDirectionalLight(strmaterial);

	fragColor = vec4(result_Dir,1);
	
}
