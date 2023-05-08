#version 430 core

in vec2 texCoords;

uniform vec3 blockColor;
uniform sampler2D tex;

out vec4 fragColor;

void main(){

	vec4 color = texture(tex,texCoords);
	color *= vec4(color.xyz * blockColor,color.w);
	if(color.w != 0) fragColor = color;
	else discard;


}