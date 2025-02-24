// This file is part of the course TPV2@UCM - Samir Genaim

#include "NewRoundState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "AsteroidsFacade.h"
#include "BlackHoleFacade.h"
#include "FighterFacade.h"
#include "Game.h"
#include "MisilesFacade.h"

NewRoundState::NewRoundState(AsteroidsFacade *ast_mngr, BlackHoleFacade* holes_mngr,
		FighterFacade *fighter_mngr, MissilesFacade* misile_mngr) :
		msg_(sdlutils().msgs().at("newround")), //
		ihdlr(ih()), //
		ast_mngr_(ast_mngr), //
		holes_mngr(holes_mngr), //
		fighter_mngr_(fighter_mngr), 		
		misile_mngr_(misile_mngr) {

	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

NewRoundState::~NewRoundState() {
}

void NewRoundState::leave() {
}

void NewRoundState::update() {
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
		fighter_mngr_->reset_fighter();
		ast_mngr_->remove_all_asteroids();
		misile_mngr_->remove_all_missiles();
		ast_mngr_->create_asteroids(10);
		holes_mngr->remove_all_black_holes();
		holes_mngr->create_black_holes(6);
		Game::instance()->setState(Game::RUNNING);
	}
	sdlutils().clearRenderer();
	msg_.render(dest_);
	sdlutils().presentRenderer();
}

void NewRoundState::enter() {
}
