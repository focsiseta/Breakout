#include "manager.h"

std::unordered_map<std::string,Texture>ResourceManager::textures{};

void ResourceManager::LoadTexture(std::string path,std::string name) {

	auto result = textures.insert(std::make_pair(name, Texture{ path }));
	//TODO
	if (!result.second) std::cout << "LOG ERROR : Texture hasn't been inserted \n";


}