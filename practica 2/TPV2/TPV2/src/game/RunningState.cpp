#include "RunningState.h"
#include "Game.h"

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
    // Aquí limpias los recursos si es necesario
    ;
}

void RunningState::enter() {
    // Inicialización específica del estado Running
    // Si necesitas acceso al Manager puedes obtenerlo desde Game::instance().getMngr()
    ;
}

void RunningState::exit() {
    // Limpieza específica del estado Running
    ;
}

void RunningState::update() {

    auto mngr = Game::instance().getMngr();

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
        Game::instance().setState(Game::GAMEOVER);
        return;
    }
    if (currentl != pacmanSys_->getlives()) {
        Game::instance().setState(Game::NEWROUND);
        pacmanSys_->loseLife();
        return;
    }

}