#version 330 core

in vec4 vertcolor;
out vec4 dfragColor;

void main()
{
	dfragColor = vertcolor;
}