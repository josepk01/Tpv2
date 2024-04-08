#include "NewGameState.h"
#include "Game.h"
#include "NewRoundState.h"
#include "../sdlutils/InputHandler.h"

void NewGameState::enter(Game* game) {
    // Setup para NewGameState
    // Posiblemente reiniciar alguna lógica de juego, puntuaciones, etc.
}

void NewGameState::exit(Game* game) {
    // Limpieza para NewGameState si es necesario
}

void NewGameState::update(Game* game) {
    // Si el usuario pulsa cualquier tecla, cambiamos al estado NewRoundState
    if (ih().keyDownEvent()) {
        game->changeState(new NewRoundState());
    }
}
