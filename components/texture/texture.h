#pragma once
#ifndef __TEXTURE
#define __TEXTURE
#include "../context/context.h"
#include <stb_image.h>
class Texture {
private:
	GLuint ID;
	std::string path;
public:
	Texture(std::string path);
	Texture();
	void bind(unsigned int);
};
#endif