#pragma once
#include "../../libraries/glm/glm.hpp"
#include "../../components/texture/texture.h"
#include "../../components/shader/shader.h"
#include "../../components/context/context.h"
#define _USE_MATH_DEFINES
#include <math.h>


class Sprite {
private:
	glm::vec2 position;
	float rotation;
	float scaleFactor;
	glm::mat4 model;
	Texture texture;
	Shader shader;
	static float vertices[12];

public:
	Sprite();
	void traslate(glm::vec2);
	void rotate(float degree);
	void scale(float size);
	void draw(Shader& sh);
	static GLuint ID; //VAO obj
	static void initSprites();



};