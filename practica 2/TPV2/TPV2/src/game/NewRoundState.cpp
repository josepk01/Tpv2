#include "NewRoundState.h"
#include "Game.h"
#include "RunningState.h"
#include "../sdlutils/InputHandler.h"

void NewRoundState::enter() {
    // Setup para NewRoundState
    // Podr�as inicializar la ronda aqu�
}

void NewRoundState::exit() {
    // Limpieza para NewRoundState si es necesario
}

void NewRoundState::update() {
    // Si el usuario pulsa ENTER, cambiamos al estado RunningState
    if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {
        //game->changeState(new RunningState());
    }
}
