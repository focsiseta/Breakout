#version 430 core
in vec2 texCoords;
in vec2 oPosition;
out vec4 fragColor;


uniform float life;
uniform vec4 particleColor;
uniform sampler2D particle;

void main(){
	
	vec4 color = texture(particle,texCoords);
	color *= life;
	if(color.a <= 0) discard;
	fragColor = color;


}