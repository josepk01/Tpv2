
#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "LittleWolf.h"

#include "Networking.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Collisions.h"


Game::Game() :
	little_wolf_(nullptr), //
	net_(nullptr)
{
}

Game::~Game() {
	delete little_wolf_;
	delete net_;
}

bool Game::init(char* host, Uint16 port) {

	net_ = new Networking();

	if (!net_->init(host, port)) {
		SDLNetUtils::print_SDLNet_error();
	}
	std::cout << "Connected as client " << (int)net_->client_id() << std::endl;

	// initialize the SDLUtils singleton
	SDLUtils::init("Demo", 900, 480,
		"resources/config/littlewolf.resources.json");


	little_wolf_ = new LittleWolf(sdlutils().width(), sdlutils().height(),
		sdlutils().window(), sdlutils().renderer());

	// load a map
	little_wolf_->load("resources/maps/little_wolf/map_0.txt");

	// add some players

	//little_wolf_->addPlayer(net_->client_id());
	little_wolf_->addPlayer(net_->client_id());
	//little_wolf_->addPlayer(1);
	//little_wolf_->addPlayer(2);
	//little_wolf_->addPlayer(3);

	return true;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto& ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();
		if (ihdlr.keyDownEvent()) {

			// ESC exists the game
			if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				exit = true;
				continue;
			}

			// N switches to the next player view
			//if (ihdlr.isKeyDown(SDL_SCANCODE_N)) {
			//	little_wolf_->switchToNextPlayer();
			//}

			//// R brings deads to life
			//if (ihdlr.isKeyDown(SDL_SCANCODE_R)) {
			//	little_wolf_->bringAllToLife();
			//}

		}

		little_wolf_->update();
		net_->update();

		//net_->send_state(little_wolf_->get_x(), little_wolf_->get_x());
		// the clear is not necessary since we copy the whole texture -- I guess ...
		sdlutils().clearRenderer();

		little_wolf_->render();

		sdlutils().presentRenderer();


		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

	net_->disconnect();
}

