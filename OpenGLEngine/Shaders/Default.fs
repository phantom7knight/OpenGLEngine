#version 330 core 


in vec4 vertexcolor;
out vec4 color;
void main()
{
	//gl_pos = vec4(triangle_vertices,1.0);
	//vertexcolor = vec4(1.0,0.0,0.0,1.0);
	color = vertexcolor;
}