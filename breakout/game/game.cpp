#include "game.h"

/*

	1 1 1 1 0 0 2 2 2 2
	1 1 1 1 1 1 1 1 1 1
	3 3 3 3 3 3 3 3 3 3


*/

//directions

const glm::vec2 right = glm::vec2(1, 0);
const glm::vec2 down = glm::vec2(0, 1);

//TODO Fixare come vengono disegnati i livelli
GameLevel::GameLevel() {}
void GameLevel::loadLevel(std::string path) {

	std::string file = readFromFile(path.c_str());
	int columns = 0;
	int rows = 0;
	int maxColumns = 0;
	
	//Ugly function
	std::vector<Sprite> tmpBlocks{};
	for (auto a : file) {
		
		switch (a) {

			case '0': {
				tmpBlocks.push_back(Sprite{ "./breakout/assets/block_solid.png",glm::vec3(1) });
				columns++;
				break;
			}
			case '1': {
				tmpBlocks.push_back(Sprite{ "./breakout/assets/block.png",glm::vec3(0,0,1)});
				columns++;
				break;

			}
			case '2': {
				tmpBlocks.push_back(Sprite{ "./breakout/assets/block.png",glm::vec3(0,1,0) });
				columns++;
				break;
			}
			case '3': {
				tmpBlocks.push_back(Sprite{ "./breakout/assets/block.png",glm::vec3(1,0,0) });
				columns++;
				break;
			}
			case '\n': {
				
				tmpBlocks.push_back(Sprite{});
				if (maxColumns < columns) maxColumns = columns;
				columns = 0;
				rows++;
				break;
			}
			default: continue;

		};
	}
	//Calcs for block size 
	std::pair<float, float> w_h = GameLevel::sizeCalc(rows, maxColumns);
	int cCounter = 0;
	int rCounter = 0;
	for (Sprite a : tmpBlocks) {

		//std::cout << a.color[0] << " " << a.color[1] << " " << a.color[2] << " " << rows << " " << columns << std::endl;
		
		if (a.hasTexture) {
			a.scale(glm::vec2(w_h.first, w_h.second));
			a.traslate(glm::vec2(w_h.first * cCounter, w_h.second * rCounter));
			this->blocks.push_back(a);
			cCounter++;
			continue;
		}
		cCounter = 0;
		rCounter++;

	}

}

GameLevel::GameLevel(std::string path) {

	this->loadLevel(path);

}

Ball::Ball(std::string texturePath,float radius,glm::vec2 direction,glm::vec2 position) : Sprite(texturePath,glm::vec3(1)) {
	
	
	this->radius = radius;
	this->direction = direction;
	this->stuck = true;
	this->scale(glm::vec2(radius));
	
	this->traslate(position);
}
Ball::Ball() {};
void Ball::move(float step) {
	
	if (!this->stuck) {
	
		this->position += this->direction * step;
		
		if (this->position.x <= 0.f || 
			this->position.x + this->radius >= float(WIN_WIDTH)) {
			
			this->direction.x = -this->direction.x;

		}
		if (this->position.y <= 0 ||
			this->position.y + this->radius >= float(WIN_HEIGHT)) {
			this->direction.y = -this->direction.y;
		}
	
	
	}

}
bool check(Sprite& obj1, Sprite& obj2) {

	bool collisionX = obj1.position.x + obj1.scaleFactor.x >= obj2.position.x &&
		obj2.position.x + obj2.scaleFactor.x >= obj1.position.x;
	bool collisionY = obj1.position.y + obj1.scaleFactor.y >= obj2.position.y &&
		obj2.position.y + obj2.scaleFactor.y >= obj1.position.y;

	return collisionX && collisionY;

}

std::pair<dirIndex,float> Ball::checkCollision(Sprite& obj) {
	
	glm::vec2 objCenter = glm::vec2(obj.position + obj.scaleFactor / 2.f);
	glm::vec2 ballCenter = glm::vec2(this->position + this->scaleFactor / 2.f);

	//Direction from obj to ball
	auto direction = ballCenter - objCenter;
	direction = glm::clamp(direction,-obj.scaleFactor / 2.f, obj.scaleFactor / 2.f);
	auto onAABB = objCenter + direction;
	auto ballToAABB = onAABB - ballCenter;

	 // <= 0 e' hit
	float hit = glm::length(ballToAABB) - this->radius;
	dirIndex hitted = RIGHT;
	float max = -1;
	if (hit <= 0) {
		ballToAABB = -glm::normalize(ballToAABB);

		glm::vec4 angles = glm::vec4(
			glm::dot(ballToAABB, right),
			glm::dot(ballToAABB, -right),
			glm::dot(ballToAABB, -down),
			glm::dot(ballToAABB, down)
		);
		dirIndex face[4] = { 
			RIGHT,
			LEFT,
			UP,
			DOWN };

			for (int i = 0; i < 4; i++) {

				if (max <= angles[i]) {
					max = angles[i];
					hitted = face[i];

				}


			}
	
	
	}


	return std::pair<dirIndex, float>{hitted,max};
}

void GameLevel::drawLevel(Shader& sh) {
	
	

	for (Sprite a : this->blocks) {
		if (a.isAlive) {
			a.bindTexture();
			sh.u_vec3(a.color, "blockColor");
			a.draw(sh);
		}


	}

};

std::pair<float,float> GameLevel::sizeCalc(int nRows, int nColmn) {
	//For now field will occupy only 80% of the window height
	float usableHeight = WIN_HEIGHT / 1.f;

	float widthOfBlock = WIN_WIDTH / float(nColmn);

	std::cout << widthOfBlock << std::endl;

	float heightOfBlock = usableHeight / float(nRows);


	return std::pair<float,float>(widthOfBlock, heightOfBlock);
	


}




Game::Game(std::string texPaddle, std::string texBall,float radius ,glm::vec2 initialBallDirection) {
	//TODO automatizzare la posizone del paddle centrata e abbassata
	this->paddle = Sprite(texPaddle, glm::vec3(1));
	this->paddle.scale(glm::vec2(200, 50));
	this->paddle.traslate(glm::vec2(WIN_WIDTH / 2.f - this->paddle.scaleFactor.x, WIN_HEIGHT - this->paddle.scaleFactor.y));
	this->ball = Ball(texBall,
		radius,
		initialBallDirection,
		//Ball position
		glm::vec2(this->paddle.position.x + this->paddle.scaleFactor.x /2. - radius /2.,
			this->paddle.position.y - (radius)));
	
	this->in = Input();
	this->levelIn = 0;



};

void Game::movement() {
	//Inertia of ball
	float momento = 0.f;

	bool isStuck = this->ball.stuck;
	if (in[GLFW_KEY_A]) {
		this->paddle.traslate(glm::vec2(-PLAYER_X_MOVEMENT, 0));
		if (isStuck) this->ball.traslate(glm::vec2(-PLAYER_X_MOVEMENT, 0));
		momento = -float(PLAYER_X_MOVEMENT);

	}
	if (in[GLFW_KEY_D]) {
		this->paddle.traslate(glm::vec2(PLAYER_X_MOVEMENT, 0));
		if (isStuck) this->ball.traslate(glm::vec2(PLAYER_X_MOVEMENT, 0));
		momento = float(PLAYER_X_MOVEMENT);

	}
	if (in[GLFW_KEY_SPACE] && isStuck) { 
		this->ball.stuck = !this->ball.stuck;
		this->ball.position.y = this->ball.position.y - 3.;
		this->ball.direction = glm::vec2(momento, -5);
	}
	if (!this->ball.stuck) this->ball.move(1.f);

}

void Game::drawPaddleAndBall(Shader& sh) {
	sh.use();
	this->ball.bindTexture();
	sh.u_vec3(this->ball.color, "blockColor");
	this->ball.draw(sh);
	this->paddle.bindTexture();
	sh.u_vec3(this->paddle.color, "blockColor");
	this->paddle.draw(sh);
}

void Game::addLevel(std::string path) {
	
	//TODO error handling
	this->levels.push_back(GameLevel::GameLevel(path));

}

void Game::drawLevel(Shader& sh,int i) {
	sh.use();
	this->levels[i].drawLevel(sh);

}

void Game::doCollisions() {

	GameLevel& level = this->levels[this->levelIn];
	auto paddleHit = this->ball.checkCollision(this->paddle);
	auto paddleFace = paddleHit.first;
	float paddleCenter = this->paddle.position.x + this->paddle.scaleFactor.x / 2.f;
	float distance = this->ball.position.x + this->ball.scaleFactor.x / 2.f;
	distance = distance - paddleCenter;
	float percentage = distance / (this->paddle.scaleFactor.x / 2.f);
	//Hit con la paddle
	if (paddleHit.second >= 0.f && !this->ball.stuck) {
		auto oldVelocity = this->ball.direction;
		this->ball.direction = glm::vec2(
		this->ball.direction.x, -oldVelocity.y);
		return;
	
	}

	for (Sprite& block : level.blocks) {
			
		if (block.isAlive) {

			auto hit = this->ball.checkCollision(block);
			if (hit.second >= 0.f) {

				block.isAlive = false;
				auto face = hit.first;
				if (face == RIGHT || face == LEFT)
					this->ball.direction = glm::vec2(
						-this->ball.direction.x, this->ball.direction.y);

				if (face == UP || face == DOWN)
					this->ball.direction = glm::vec2(
						this->ball.direction.x, -this->ball.direction.y);


			}
		
		}

	
	}



}



