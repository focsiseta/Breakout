#version 430 core

layout (location = 0) in vec2 aPos;
uniform mat4 projection;
uniform mat4 model;

out vec2 texCoords;
out vec4 worldPos;


void main(){
	
	vec4 wPosition = vec4(aPos,0,1);
	texCoords = aPos;
	worldPos = (model * (wPosition));
	gl_Position = projection * worldPos;


}