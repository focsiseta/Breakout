#include "particles.h"



Particle::Particle() {
	this->Position = glm::vec2(0);
	this->Direction = glm::vec2(0, 1);
	this->Color = glm::vec4(1);
	this->life = 1.0;

	//Default texture
	this->image = Texture("./breakout/assets/cursor.png");

}
Particle::Particle(glm::vec2 pos, glm::vec2 direction, glm::vec4 color,Texture tex,float health)
	: Position(pos), Direction(direction), Color(color), life(health),image(tex){}

Particle::Particle(const Particle& obj, Texture tex) {
	this->Position = obj.Position;
	this->Direction = obj.Direction;
	this->Color = obj.Color;
	this->life = obj.life;

	
	this->image = tex;
	

}



ParticleGenerator::ParticleGenerator(Particle& obj,Ball& ball, unsigned int quantity,
										unsigned int spawnRate) : reference(ball) {

	

	this->particles = std::vector<Particle>();
	for (unsigned int i = 0; i < quantity; i++) {
		
		this->particles.push_back(Particle(obj));

	}
	this->spawnRate = spawnRate;
	this->nOfParticles = quantity;
	this->initializeAlive();

	

}
ParticleGenerator::ParticleGenerator(Particle& obj,Ball& sprite) : reference(sprite){

	
	this->particles = std::vector<Particle>();
	for (unsigned int i = 0; i < DEFAULT_PARTICLES; i++) {

		this->particles.push_back(Particle(obj));
		

	}
	this->spawnRate = DEFAULT_PARTICLES;
	this->nOfParticles = DEFAULT_PARTICLES;
	this->initializeAlive();

}

void ParticleGenerator::initializeAlive() {
	
	for (Particle& sample : this->particles) {
	
		this->alive.push_back(sample);

	}

}

void ParticleGenerator::respawnParticle(Particle& obj){
	
	
	//I should be really thanking The Book of Shaders and all the fantastic people behind it ngl
	//The more I read that book the more I understand

	glm::vec2 random = glm::vec2(glm::fract(sin(
		glm::dot(this->reference.position, glm::vec2(824.638f, 218.934f))
	)* 4234.2934f));
	obj.Position = this->reference.position + random;
	obj.Direction = this->reference.direction * random.x;
	obj.life = 1.0f;
	this->alive.push_back(obj);
	


}

Particle& ParticleGenerator::firstDead() {
	
	//TODO Linear search, could be better
	for (Particle& part : this->particles) {
		if (part.life <= 0.f) return part;
	}

}

void ParticleGenerator::update() {

	//if (!this->reference.stuck) {
		
		for (unsigned int i = 0; i < this->spawnRate; i++) {

			Particle& dead = this->firstDead();
			this->respawnParticle(dead);

		}
		for (Particle& part : this->particles) {

			part.life -= 0.02;
			if (part.life >= 0.f) {

				part.Position -= part.Direction * 0.02f * part.life;

			}

		}
	
	//}

	/*

		glm::vec2 random = glm::vec2(glm::fract(sin(
		glm::dot(this->reference.position, glm::vec2(824.638f, 218.934f))
	) * 4234.2934f));
		*/





}


GLuint ParticleGenerator::ID = 0;

void ParticleGenerator::init() {

	float vertices[12] = {
	0.,0.,
	0.,1.,
	1.,0.,
	0.,1.,
	1.,1.,
	1.,0.,


	};

	//https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions#glcreatebuffers

	glGenVertexArrays(1,&ParticleGenerator::ID);
	GLuint id;
	glBindVertexArray(ParticleGenerator::ID);
	glCreateBuffers(1, &id);
	
	glNamedBufferData(id,sizeof(vertices),&vertices,GL_STATIC_DRAW);
	glBindVertexBuffer(0,id,0,sizeof(float) * 2);


	glEnableVertexAttribArray(0);

	glVertexAttribFormat(0,2,GL_FLOAT,false,0);
	glBindVertexArray(0);


}

void ParticleGenerator::render(Shader& sh) {
	sh.use();
	glBindVertexArray(ParticleGenerator::ID);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		for (Particle& particle : this->particles) {

			sh.u_vec2(particle.Position, "position");
			sh.u_vec4(particle.Color, "particleColor");
			sh.u_float(this->reference.radius, "radius");
			sh.u_float(particle.life, "life");
			particle.image.bind(0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

		}
	//glBindVertexArray(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	auto errorCode = glGetError();
	//std::cout << errorCode << "Error code \n";


}