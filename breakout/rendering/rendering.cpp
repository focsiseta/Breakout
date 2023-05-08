#include "rendering.h"

//
float Sprite::vertices[12] = {
	0.,0.,
	0.,1.,
	1.,0.,
	0.,1.,
	1.,1.,
	1.,0.,


};
GLuint Sprite::ID = 0;

Sprite::Sprite() {

	this->model = glm::mat4(1.);
	this->rotation = 0;
	this->position = glm::vec2(0.);
	this->scaleFactor = glm::vec2(1);
	this->hasTexture = false;
	this->color = glm::vec3(0);


}

Sprite::Sprite(std::string path){
	this->model = glm::mat4(1.);
	this->rotation = 0; 
	this->position = glm::vec2(0.);
	this->scaleFactor = glm::vec2(1);
	this->texture = Texture(path);
	this->hasTexture = true;
	this->color = glm::vec3(0);



}

Sprite::Sprite(std::string path, glm::vec3 color) {

	this->model = glm::mat4(1.);
	this->rotation = 0;
	this->position = glm::vec2(0.);
	this->scaleFactor = glm::vec2(1);
	this->texture = Texture(path);
	this->hasTexture = true;
	this->color = color;

}

//Puts vertex data onto GPU
void  Sprite::initSprites() {

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1,&VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(Sprite::vertices),&Sprite::vertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Sprite::ID = VAO;
	if (glGetError() != GL_NO_ERROR) std::cout << "error" << std::endl;

}

void Sprite::draw(Shader& sh) {
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model,glm::vec3(this->position,0));

	model = glm::translate(model, glm::vec3(0.5 * this->scaleFactor[0], 0.5 * this->scaleFactor[1], 0.0));

	model = glm::rotate(model, this->rotation, glm::vec3(0, 0, 1));

	model = glm::translate(model, glm::vec3(-0.5 * this->scaleFactor[0], -0.5 * this->scaleFactor[1], 0.0));


	model = glm::scale(model, glm::vec3(this->scaleFactor, 0));


	this->model = model;
	sh.u_mat4(this->model, "model", false);
	glBindVertexArray(Sprite::ID);
	glDrawArrays(GL_TRIANGLES,0,6);
	if (glGetError() != GL_NO_ERROR) std::cout << "error" << std::endl;

}

void Sprite::traslate(glm::vec2 toGo) {
	
	this->position += toGo;


}
void Sprite::rotate(float degree) {

	float rads = degree * (M_PI / 180);
	this->rotation += rads;

}
void Sprite::scale(glm::vec2 size) {
	
	this->scaleFactor = size;
	if (this->scaleFactor[0] <= 0 && this->scaleFactor[1] <= 0) this->scaleFactor = glm::vec2(1);

}

void Sprite::bindTexture() {

	if (this->hasTexture)
		this->texture.bind(0);

}
void Sprite::bindTexture(int unit) {

	if (this->hasTexture)
		this->texture.bind(unit);

}