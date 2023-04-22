#version 430 core

in vec2 texCoords;

out vec4 fragColor;

void main(){

	fragColor = vec4(texCoords,0,0);


}