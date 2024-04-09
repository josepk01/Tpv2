#include "RunningState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"


RunningState::RunningState() {
    auto mngr = Game::instance().getMngr();


     gameCtrlSys_ = mngr->getSystem<GameCtrlSystem>();

     pacmanSys_ = mngr->getSystem<PacManSystem>();
     ghostSys_ = mngr->getSystem<GhostSystem>();
     foodSys_ = mngr->getSystem<FruitSystem>();

     render_system = mngr->getSystem<RenderSystem>();
     collisionSys_ = mngr->getSystem<CollisionsSystem>();


     currentl = pacmanSys_->getlives();
}

RunningState::~RunningState() {
    // Aqu� limpias los recursos si es necesario
    ;
}

void RunningState::enter() {
    // Inicializaci�n espec�fica del estado Running
    // Si necesitas acceso al Manager puedes obtenerlo desde Game::instance().getMngr()
    ;
}

void RunningState::exit() {
    // Limpieza espec�fica del estado Running
    ;
}

void RunningState::update() {

    std::cout << "runing";
    gameCtrlSys_->update();

	pacmanSys_->update();
	foodSys_->update();
	ghostSys_->update();
	collisionSys_->update();
    sdlutils().clearRenderer();
    render_system->update();
    sdlutils().presentRenderer();

    // move to pause if P pressed
    if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_P)) {
        Game::instance().setState(Game::PAUSED);
        return;
    }
    if (foodSys_->getfruit() <= 0) {
        Game::instance().setState(Game::GAMEOVER);
        return;
    }
    if (pacmanSys_->getlives() <= 0) {
        pacmanSys_->reset();
        Game::instance().setState(Game::GAMEOVER);
        return;
    }
    if (currentl != pacmanSys_->getlives()) {
        Game::instance().setState(Game::NEWROUND);
        pacmanSys_->loseLife();
        currentl = pacmanSys_->getlives();
        return;
    }

}