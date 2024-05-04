// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../utils/Singleton.h"
#include "Stick.h"


class LittleWolf;
class Networking;

class Game : public Singleton<Game> {
public:
	Game();
	virtual ~Game();
	bool init(char* host, Uint16 port);
	void start();

	Stick& get_sticks() {
		return *sticks_;
	}

	Networking& get_networking() {
		return *net_;
	}
private:
	LittleWolf *little_wolf_;
	Networking* net_;
	Stick* sticks_;
};

