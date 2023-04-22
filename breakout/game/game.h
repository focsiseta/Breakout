#pragma once
#ifndef __BRK
#define __BRK

enum GameState {

	G_MENU,
	G_GAME,
	G_END,

};

class Game {
	GameState state;
	bool keys[1024] = { false };



};


#endif