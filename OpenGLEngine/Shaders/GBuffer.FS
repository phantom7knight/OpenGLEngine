#version 430 core

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normals;


out vec4 FragColor;

layout(location = 0) out vec3 gPosition;
//layout(location = 1) out vec3 gNormal;
//layout(location = 2) out vec4 gAlbedoandSpec;

uniform sampler2D AlbedoTexture;
//uniform sampler2D specularmap;



void main()
{
    //gNormal = normalize(Normals);

    gPosition =  texture(AlbedoTexture,TexCoords).rgb;//vec3(1,0,1);//FragPos;

    //gAlbedoandSpec.xyz = vec3(1,0,1);// texture(AlbedoTexture,TexCoords).rgb;
    
    //gAlbedoandSpec.z = 1.0;//texture(AlbedoTexture,TexCoords).r;   

    //FragColor = vec4(FragPos,1.0f); 
    
}