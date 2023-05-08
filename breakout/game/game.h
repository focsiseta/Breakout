#pragma once
#ifndef __BRK
#define __BRK
#include "../rendering/rendering.h"
#include "../../components/context/context.h"
#include "../../components/input/input.h"
#include "../../components/shader/shader.h"
#include <vector>
bool check(const Sprite& obj1, Sprite& obj2);

enum GameState {

	G_MENU,
	G_GAME,
	G_END,

};

enum dirIndex {
	RIGHT,
	LEFT,
	UP,
	DOWN


};

class GameLevel {

public:
	GameLevel();
	GameLevel(std::string);
	std::vector<Sprite> blocks;
	void loadLevel(std::string);
	void drawLevel(Shader&);
private:
	static std::pair<float,float> sizeCalc(int,int);
};

class Ball : public Sprite{

public:
	Ball();
	float radius;
	glm::vec2 direction;
	bool stuck;

	Ball(std::string,float,glm::vec2, glm::vec2);
	void move(float step);
	//Could be optimized just returning a single vec3
	std::pair<dirIndex, float> checkCollision(Sprite&);




};
#define PLAYER_X_MOVEMENT 2.0f

class Game {
public:
	Game(std::string texPaddle,std::string texBall,float radius,
		glm::vec2 initialBallDirection);
	void movement();
	void drawPaddleAndBall(Shader&);
	void addLevel(std::string path);
	void drawLevel(Shader&, int);
	void doCollisions();
	GameState state;
	Input in;
	Sprite paddle;
	Ball ball;
	int levelIn;

	std::vector<GameLevel> levels;


};


#endif