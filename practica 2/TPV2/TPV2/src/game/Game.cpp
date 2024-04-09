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
#include "GameOverState.h"
#include "NewGameState.h"
#include "NewRoundState.h"
#include "PauseState.h"
#include "RunningState.h"
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

	paused_state_ = new PauseState();
	runing_state_ = new RunningState();
	newgame_state_ = new NewGameState();
	newround_state_ = new NewRoundState();
	gameover_state_ = new GameOverState();


	current_state_ = newgame_state_;
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

		sdlutils().clearRenderer();
		current_state_->update();
		sdlutils().presentRenderer();
		mngr_->refresh();



		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}


void Game::changeState(GameState* newState) {
	if (current_state_ != nullptr) {
		current_state_->exit();
	}
	current_state_ = newState;
	if (current_state_ != nullptr) {
		current_state_->enter();
	}
}

