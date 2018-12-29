#version 330 core 

layout(location = 0) in vec3 triangle_vertices;

//uniform vec3 tempVert;
//uniform mat4 mWorldMat;

out vec4 vertexcolor;

void main()
{
	//gl_Position = mWorldMat*vec4(triangle_vertices,1.0);
	//vertexcolor = vec4(color,1.0);

	gl_Position = vec4(triangle_vertices,1.0);
	vertexcolor = vec4(0.0,0.0,1.0,1.0);
}