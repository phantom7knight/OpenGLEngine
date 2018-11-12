#version 330 core

out vec4 fragColor;

in vec3 Normals;
in vec3 Fragpos;


uniform vec3 objectCol;
uniform vec3 cameraPos;
uniform vec3 lightPos;

uniform float DeltaTime;

vec3 objectColor;

vec3 CalculateDirectionalLight()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	//Normalize Object Color
	//objectColor = normalize(objectCol);
	
	//Ambient Color
	vec3 ambientColor = vec3(1.0f,1.0f,1.0f);
	float ambientStrength = 1.5;
	ambient = ambientStrength * ambientColor * (objectCol);
	
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
	
	return (specular + ambient + diffuse);
	//return ( vec3(spec,spec,spec) );
}



void main()
{
	vec3 result_Dir = CalculateDirectionalLight();

	fragColor = vec4(result_Dir,1);
	//fragColor = vec4(1.0,0.0,1.0,1.0);
	
}
