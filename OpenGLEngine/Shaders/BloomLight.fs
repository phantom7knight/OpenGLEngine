#version 330 core


layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;


out vec4 fragColor;

in vec3 Normals;
in vec3 Fragpos;
in vec2 TexCoords;

uniform vec3	objectCol;

uniform vec3	cameraPos;


uniform vec3	lightPos;
uniform float 	Lightintensity;

uniform vec3 LightColor;

vec3 threshold = vec3(0.2126,0.7152,0.0722);

void main()
{
	
	FragColor = vec4(LightColor,1.0);

	float Brightness = dot(FragColor.rgb,threshold);

	if(Brightness > 1.0)
	{
		BrightColor = FragColor;
	}

}
