// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;

class AsteroidsFacade;

class MissilesFacade;

class BlackHoleFacade;
class FighterFacade;

class NewRoundState: public GameState {
public:
	NewRoundState(AsteroidsFacade *ast_mngr, BlackHoleFacade* holes_mngr, FighterFacade *fighter_mngr, MissilesFacade* misile_mngr);

	virtual ~NewRoundState();
	void enter() override;
	void leave() override;
	void update() override;

private:
	Texture &msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
	AsteroidsFacade *ast_mngr_;
	BlackHoleFacade* holes_mngr;
	FighterFacade *fighter_mngr_;
	MissilesFacade *misile_mngr_;

};

