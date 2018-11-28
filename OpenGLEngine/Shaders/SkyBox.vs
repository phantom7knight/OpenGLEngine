#version 330 core

layout(location = 0) in vec3 position;

out vec3 TexCoords;

uniform mat4 Model_Matrix ;
uniform mat4 View_matrix;
uniform mat4 Projection_matrix ;

void main()
{
	
	gl_Position		=  Projection_matrix  * View_matrix * Model_Matrix * vec4(position,1.0);
	TexCoords		=  position;

}