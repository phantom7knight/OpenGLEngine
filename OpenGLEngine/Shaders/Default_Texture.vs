#version 330 core

layout(location = 0) in vec4 triangle_vertices; //This takes vertices to draw a triangle or a square from
//layout(location = 1) in vec2 TexCords;

out vec4 vertcolor;								//This is used to send the color of the vertex to Fragment Shader

uniform vec4 Color_Send;						//Color to be applied on the object this is sent from outside
uniform mat4 worldmat;							//This is responsible for change in the transformations

out vec2 cords_tex;								//This is used for the positions of the texture where it should it be placed

void main()
{
	gl_Position = worldmat*vec4(triangle_vertices.xy,1.0,1.0);
	vertcolor = Color_Send;
	cords_tex = triangle_vertices.zw;//TexCords;
}