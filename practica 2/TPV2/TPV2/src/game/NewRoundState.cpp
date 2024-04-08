#include "NewRoundState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"

NewRoundState::NewRoundState() {
    // Constructor vac�o
}

NewRoundState::~NewRoundState() {
    // Destructor, limpia recursos si es necesario
}

void NewRoundState::enter() {
    // Configuraci�n para NewRoundState
}

void NewRoundState::exit() {
    // Limpieza para NewRoundState si es necesario
}

void NewRoundState::update() {
    // Si el usuario pulsa ENTER, cambiamos al estado RunningState
    if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {
       Game::instance().changeState(new RunningState());
    }
}
