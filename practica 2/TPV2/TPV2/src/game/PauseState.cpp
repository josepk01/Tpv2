#include "PauseState.h"
#include "Game.h"
#include "RunningState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PauseState::PauseState() {}

PauseState::~PauseState() {}

void PauseState::enter() {
    sdlutils().virtualTimer().pause();
}

void PauseState::update() {
	if (ih().keyDownEvent()) {
		Game::instance().setState(Game::RUNNING);
	}
	sdlutils().clearRenderer();
	sdlutils().presentRenderer();
}

void PauseState::leave() {
    sdlutils().virtualTimer().resume();
}
