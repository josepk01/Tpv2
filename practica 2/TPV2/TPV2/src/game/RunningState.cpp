#include "RunningState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/GhostSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"

RunningState::RunningState() {
    // Aqu� podr�as inicializar recursos si es necesario
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

    auto mngr = Game::instance().getMngr();

    if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::instance().setState(Game::PAUSED);
        return;
    }

    GameCtrlSystem* gameCtrlSys_ = mngr->getSystem<GameCtrlSystem>();

    PacManSystem* pacmanSys_ = mngr->getSystem<PacManSystem>();
    GhostSystem* ghostSys_ = mngr->getSystem<GhostSystem>();
    FruitSystem* foodSys_ = mngr->getSystem<FruitSystem>();

    RenderSystem* render_system = mngr->getSystem<RenderSystem>();
    CollisionsSystem* collisionSys_ = mngr->getSystem<CollisionsSystem>();



    gameCtrlSys_->update();

	pacmanSys_->update();
	foodSys_->update();
	ghostSys_->update();
	collisionSys_->update();
    render_system->update();

}