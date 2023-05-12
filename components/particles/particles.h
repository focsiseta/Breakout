#pragma once

#ifndef __PARTICLES
#define __PARTICLES
#include <vector>
#include <cmath>
#include <functional>
#define GLM_FORCE_PRECISION_LOWP_FLOAT
#include "../../libraries/glm/glm.hpp"
#include "../../components/texture/texture.h"
#include "../../components/shader/shader.h"
#include "../../breakout/game/game.h"
#include "../../components/context/context.h"
//#include "../../breakout/game/game.h"

#define DEFAULT_PARTICLES 5
#define PARTICLE_HEALTH_LOSS 0.05


class Particle{

public:
	glm::vec2 Position, Direction;
	glm::vec4 Color;
	Texture image;
	float life;
	//copy constructor
	Particle(const Particle&,Texture tex);

	Particle();
	Particle(glm::vec2, glm::vec2, glm::vec4,Texture,float);

};

class ParticleGenerator {

private:

	static GLuint ID;
	unsigned int nOfParticles = 0;
	unsigned int spawnRate = 0;
	Ball& reference; //This needs to be changed in something more generic like a game object class

	//TODO If I want to generalize this piece of code I need to create a new class which acts as a generic GameElement,
	//as of now Sprite doesn't hold a direction which is a more specific attribute 
	//and putting it in Sprite just to get things done would just anger me later
	
	//This is one the functions that should be generalized in some way or another
	//Loads into shader program memory all the things we don't have to update
	void initializeAlive();
	Particle& firstDead();
	void respawnParticle(Particle&);

public:

	std::vector<Particle> particles;
	//Vectors that contains alive particles and dead ones, made for fast access
	std::vector<std::reference_wrapper<Particle>> alive;
	std::vector<std::reference_wrapper<Particle>> dead;

	
	void update();
	void render(Shader& sh);
	static void init();
	
	ParticleGenerator(Particle&, Ball& , unsigned int, unsigned int);
	ParticleGenerator(Particle&, Ball&);


};
	


#endif