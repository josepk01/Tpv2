// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
//#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GhostSystem.h"

#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../systems/CollisionsSystem.h"

using ecs::Manager;

Game::Game() : mngr_(nullptr), pacmanSys_(nullptr), gameCtrlSys_(nullptr),
startsSys_(nullptr), renderSys_(nullptr), collisionSys_(nullptr),
foodSys_(nullptr), ghostSys_(nullptr)
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


	// add the systems
	pacmanSys_ = mngr_->addSystem<PacManSystem>();
	foodSys_ = mngr_->addSystem<FruitSystem>();
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
	ghostSys_ = mngr_->addSystem<GhostSystem>();
	collisionSys_ = mngr_->addSystem<CollisionsSystem>();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {

		//std::cout << "VUELTA ";

		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}


		pacmanSys_->update();
		foodSys_->update();
		gameCtrlSys_->update();
		ghostSys_->update();
		collisionSys_->update();

		mngr_->refresh();

		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::changeState(GameState* newState) {
	if (currentState != nullptr) {
		currentState->exit();
	}
	currentState = newState;
	currentState->enter();
}