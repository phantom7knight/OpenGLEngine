#version 330 core

in vec4 vertcolor;
in vec2 cords_tex;

out vec4 dfragColor;

uniform sampler2D texture_result;

void main()
{
	dfragColor = texture(texture_result,cords_tex);			// vertcolor;
}