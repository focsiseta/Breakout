#pragma once
#ifndef __MANAGER
#define __MANAGER

#include <unordered_map>

#include "../texture/texture.h"


/*

maps per la gestione delle risorse
TextureMap

*/


class ResourceManager {
private:
	static std::unordered_map<std::string, Texture> textures;
public:
	static void LoadTexture(std::string, std::string);


};


#endif
