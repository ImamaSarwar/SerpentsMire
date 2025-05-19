#pragma once
#pragma once
#include <iostream>
//#include "Players.h"
#include "Sounds.h"
using namespace std;

class Game {
protected:
	SoundSystem sound;
	//Player* player;
	virtual void startGame() = 0;
	virtual void endGame() = 0;
	~Game() {
		//delete player;
		//player = nullptr;
	}

};