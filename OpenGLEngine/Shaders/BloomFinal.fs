#version 330 core

uniform sampler2D FragColorTexture;
uniform sampler2D BlurredTexture;


uniform float exposure;
uniform int IsBloom;

in vec2 TexCoords;

out vec4 FragColor;


void main()
{
    const float gamma = 2.2;
    vec3 fragcolor1 = texture(FragColorTexture,TexCoords).rgb;
    vec3 bloomcolor = texture(BlurredTexture,TexCoords).rgb;

    //Additive Blending
   // if(IsBloom == 1)
        fragcolor1 += bloomcolor;

    //Tone Mapping
    vec3 result = vec3(1.0) - exp(-fragcolor1*exposure);

    result = pow(result,vec3(1.0/gamma));

    FragColor = vec4(result,1.0);
   //FragColor = vec4(1.0,1.0,1.0,1.0);

}