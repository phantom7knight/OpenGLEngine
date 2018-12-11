#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec3 aTexCoords;


uniform mat4 modelmat;
uniform mat4 viewmat;
uniform mat4 projectionmat;


out vec2 TexCoords;
out vec3 Normals;
out vec3 FragPos;
out vec3 center_reflection_out;

uniform vec3 center_reflection;
uniform int IsTop;

void main()
{
    FragPos = vec3(modelmat * vec4(aPosition,.0));

    vec3 R = FragPos - center_reflection;
    
    center_reflection_out =  center_reflection;

    vec3 final_res = FragPos / length(FragPos);

    Normals = mat3(transpose(inverse(modelmat))) * aNormals ;

    if(IsTop == 1)
    {
        gl_Position.xyz = vec3(final_res.x / 1 + final_res.z , final_res.y / 1 + final_res.z, final_res.z * length(final_res)/100 - 0.9); 
        gl_Position.w = 1.0;
    }
    else if( IsTop == 0)
    {
        gl_Position.xyz = vec3(final_res.x / 1 - final_res.z , final_res.y / 1 - final_res.z, -final_res.z * length(final_res)/100 - 0.9); 
        gl_Position.w = 1.0;
    }

}