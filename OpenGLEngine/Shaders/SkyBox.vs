#version 330 core

layout(location = 0) in vec3 aposition;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 atexcoords;

out vec2 TexCoords;


uniform mat4 Model_Matrix ;
uniform mat4 View_matrix;
uniform mat4 Projection_matrix ;

void main()
{
	//Use Normals to get TexCoords
	// TexCoords.x = 0.5 - atan(aNormals.y,aNormals.x)/2*3.14;
	// TexCoords.y = acos(aNormals.z)/3.14;
	
	//Inverse the TexCoords
	//TexCoords.x = cos(2*3.14(0.5 - TexCoords.x)) * sin(3.14 * TexCoords.y);
	//TexCoords.y = sin(2*3.14(0.5 - TexCoords.x)) * sin(3.14 * TexCoords.y);


	

	gl_Position		=  Projection_matrix  * View_matrix * Model_Matrix * vec4(aposition,1.0);
}