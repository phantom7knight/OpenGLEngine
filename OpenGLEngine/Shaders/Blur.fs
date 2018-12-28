#version 330 core

in vec2 TexCoords;

uniform sampler2D Image; 
uniform int IsHorizontal;

out vec4 FragColor;


uniform float weight[5] = float[](0.2270270270,0.1945945946,0.1216216216,0.0540540541,0.0162162162);

void main()
{
    vec2 tex_coords = 1.0/textureSize(Image,0);
    vec3 result = texture(Image,TexCoords).rgb * weight[0];
    

    if(IsHorizontal == 1)
    {
        for(int i = 1;i<5;++i)
        {
            result += texture(Image,TexCoords + vec2(tex_coords.x * i, 0.0)).rgb * weight[i];
            result += texture(Image,TexCoords - vec2(tex_coords.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1;i<5;++i)
        {
            result += texture(Image,TexCoords + vec2(0.0, tex_coords.y * i)).rgb * weight[i];
            result += texture(Image,TexCoords - vec2(0.0, tex_coords.y * i)).rgb * weight[i];
        }
    }
    FragColor = vec4(result,1.0);
   // FragColor = vec4(1.0,0.0,0.0,1.0);
}