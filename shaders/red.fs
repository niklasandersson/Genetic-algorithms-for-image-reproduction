#version 330 core

uniform vec3 color;
uniform float opacity;

out vec4 frag_color;

void main()
{

	frag_color.rgb = color;
	frag_color.a = opacity;
}
