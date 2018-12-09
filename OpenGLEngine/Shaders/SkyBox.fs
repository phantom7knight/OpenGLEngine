#version 330 core

out vec4 FragColor;
in vec3 TexCoords;

//uniform samplerCube textureskybox;
uniform samplerCube HDRTexture;



void main()
{

//For SkyBox
  //  vec3 result_SkyboxTexture = texture(textureskybox, TexCoords).xyz;
   // FragColor = vec4(result_SkyboxTexture,1.0f);

//For Tone Mapping for HDR Images

    const float gamma = 2.2;

    float exposure = 1.0f;

    vec3 hdrcolor = texture(HDRTexture,TexCoords).rgb;

    vec3 mapped = vec3(1.0) - exp(-hdrcolor * exposure);

    mapped = pow(mapped , vec3(1.0 / gamma));

    FragColor = vec4(mapped,1.0);

}