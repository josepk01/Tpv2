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
//    // L�gica de entrada al estado de pausa.
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
//    // Limpieza espec�fica del estado de pausa.
//}
