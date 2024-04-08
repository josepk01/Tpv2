// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
//#include "../systems/CollisionsSystem.h"


#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Manager;

Game::Game() : mngr_(nullptr)
{

}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/resources.json");

	// Create the manager
	mngr_ = new Manager();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	changeState(std::make_unique<RunningState>(mngr_));

	while (!exit) {

		//std::cout << "VUELTA ";

		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}
		
		currentState_->update();

		sdlutils().clearRenderer();

		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::changeState(std::unique_ptr<GameState> newState) {
	// Salir del estado antiguo
	if (currentState_ != nullptr) {
		currentState_->exit();
	}

	// Entrar en el nuevo estado
	currentState_ = std::move(newState);
	currentState_->enter();
}
