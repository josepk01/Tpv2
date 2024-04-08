//#include "PauseState.h"
//#include "Game.h"
//#include "RunningState.h"
//#include "../sdlutils/InputHandler.h"
//
//PauseState::PauseState() {}
//
//PauseState::~PauseState() {}
//
//void PauseState::enter() {
//    // Lógica de entrada al estado de pausa.
//}
//
//void PauseState::update() {
//    // Comprobar si se presiona alguna tecla para volver al estado Running.
//    auto& ih = ihdlr.getInstance();
//    if (ih.anyKeyDown()) {
//        Game::instance().changeState(std::make_unique<RunningState>());
//    }
//}
//
//void PauseState::leave() {
//    // Limpieza específica del estado de pausa.
//}
