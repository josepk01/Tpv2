#include "RunningState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"

RunningState::RunningState() {

    auto mngr = Game::instance().getMngr();

    gameCtrlSys_ = mngr->getSystem<GameCtrlSystem>();

    pacmanSys_ = mngr->getSystem<PacManSystem>();
    ghostSys_ = mngr->getSystem<GhostSystem>();
    foodSys_ = mngr->getSystem<FruitSystem>();

    render_system = mngr->getSystem<RenderSystem>();
    collisionSys_ = mngr->getSystem<CollisionsSystem>();
    ;
}

RunningState::~RunningState() {
    // Aqu� limpias los recursos si es necesario
    ;
}

void RunningState::enter() {
    // Inicializaci�n espec�fica del estado Running
    // Si necesitas acceso al Manager puedes obtenerlo desde Game::instance()->getMngr()
    ;
}

void RunningState::exit() {
    // Limpieza espec�fica del estado Running
    ;
}

void RunningState::update() {

    if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::instance().setState(Game::PAUSED);
        return;
    }

    gameCtrlSys_->update();

	pacmanSys_->update();
	foodSys_->update();
	ghostSys_->update();
	collisionSys_->update();
    render_system->update();

}