#version 330 core 

layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 anormals;
layout(location = 2) in vec2 aTexCoord;


uniform mat4 projectionmat;
uniform mat4 viewmat;
uniform mat4 modelmat;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normals;


void main()
{
    
    FragPos		= vec3(modelmat * vec4(apos,1.0f));

    TexCoords   = aTexCoord;
   
    Normals     = transpose(inverse(mat3(modelmat))) * anormals;

    gl_Position = projectionmat * viewmat * modelmat * vec4(apos,1.0f);

}