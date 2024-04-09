#include "GameOverState.h"
#include "Game.h"
#include "NewGameState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

void GameOverState::enter() {
    // Setup para GameOverState
    // Aqu� podr�as mostrar alg�n mensaje de Game Over
}

void GameOverState::exit() {
    // Limpieza para GameOverState si es necesario
}

void GameOverState::update() {
    // Si el usuario pulsa cualquier tecla, cambiamos al estado NewGameState
    if (ih().keyDownEvent()) {
        Game::instance().setState(Game::NEWGAME);
    }
    sdlutils().clearRenderer();
    sdlutils().presentRenderer();
}
