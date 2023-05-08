#pragma once
#include "../../libraries/glm/glm.hpp"
#include "../../components/texture/texture.h"
#include "../../components/shader/shader.h"
#include "../../components/context/context.h"
#define _USE_MATH_DEFINES
#include <math.h>


class Sprite {
private:
	float rotation;
	glm::mat4 model;
	Texture texture;
	static float vertices[12];

public:
	Sprite();
	Sprite(std::string);
	Sprite(std::string,glm::vec3 color);
	void traslate(glm::vec2);
	void rotate(float degree);
	void scale(glm::vec2 size);
	void draw(Shader& sh);
	void bindTexture();
	void bindTexture(int);
	static GLuint ID; //VAO obj
	bool hasTexture = false;
	bool isAlive = true;
	glm::vec2 scaleFactor;
	glm::vec3 color;
	glm::vec2 position;
	//Load data in gpu
	static void initSprites();



};