#include "NewGameState.h"
#include "Game.h"
#include "NewRoundState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

void NewGameState::enter() {
    // Setup para NewGameState
    // Posiblemente reiniciar alguna lógica de juego, puntuaciones, etc.
}

void NewGameState::exit() {
    // Limpieza para NewGameState si es necesario
}

void NewGameState::update() {
    // Si el usuario pulsa cualquier tecla, cambiamos al estado NewRoundState
    if (ih().keyDownEvent()) {
        Game::instance().setState(Game::NEWROUND);
    }
    sdlutils().clearRenderer();
    sdlutils().presentRenderer();
}
