#version 430 core

layout (location = 0) in vec2 iPosition;

uniform mat4 projection;
uniform vec2 position;
uniform float radius;



out vec2 texCoords;
out vec2 oPosition;

void main(){
	
	texCoords = iPosition;
	vec4 tmp =  projection * vec4((iPosition * radius) + position,0,1);
	oPosition = vec2(tmp);

	gl_Position = tmp;


}