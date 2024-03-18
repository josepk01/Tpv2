// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameState.h"

class InputHandler;
class AsteroidsFacade;
class BlackHoleFacade;
class FighterFacade;
class MissilesFacade;

class RunningState: public GameState {
public:
	RunningState(AsteroidsFacade *ast_mngr, BlackHoleFacade *holes_mngr, FighterFacade *fighter_mngr, MissilesFacade * misile_mngr);
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	void checkCollisions();
	void onFigherDeath();
	InputHandler &ihdlr;
	AsteroidsFacade *ast_mngr_;
	BlackHoleFacade * holes_mngr;
	FighterFacade *fighter_mngr_;
	MissilesFacade *misile_mngr_;
	Uint32 lastTimeGeneratedAsteroids_;
	Uint32 lastTimeGeneratedMissiles_;
	Uint32 missileGenerationInterval_;

};

