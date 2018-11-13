#version 330 core

out vec4 fragColor;

in vec3 Normals;
in vec3 Fragpos;


uniform vec3 objectCol;
uniform vec3 cameraPos;
uniform vec3 lightPos;

uniform float DeltaTime;

vec3 objectColor;

struct PointLight
{
	float constant 	;
	float linear   	;
	float quadratic	;
};

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

vec3 CalculatePointLight(PointLight pLight)
{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    pLight.constant 	= 0.10f;
    pLight.linear   	= 0.09f;
    pLight.quadratic	= 0.032f;

	//vec3 objectColor = normalize(objectCol);
	
    //Ambient Color
    vec3 ambientColor = vec3(1.0f,1.0f,1.0f);
    float ambientStrength = 0.5;
    ambient = ambientStrength * ambientColor * objectCol;

    //Diffuse 
	vec3 lightdir = normalize(lightPos - Fragpos);
	vec3 norm = normalize(Normals);
	float diff = max(dot(norm,lightdir),0.0);
	diffuse = diff * objectCol;

    //Specular
	float specularStrength = 0.5f;
	float specularIntensity = 256;
	vec3 viewdir = normalize(cameraPos - Fragpos);
	vec3 reflectdir = reflect(-lightdir,norm);
	float spec = pow(max(dot(viewdir,reflectdir),0.0),specularIntensity);
	specular = specularStrength * spec * objectCol;


	float distance = length(lightPos - Fragpos);
	float attenuation = 1.0f / (pLight.constant + pLight.linear * distance + (pLight.quadratic * distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

    return (specular + ambient + diffuse);
}

void main()
{
	PointLight pLight;
	vec3 result_Dir = CalculateDirectionalLight();
	
	vec3 result_Point = CalculatePointLight(pLight);

	fragColor = vec4(result_Dir,1);
		
}
