#include "GameOverState.h"
#include "Game.h"
#include "NewGameState.h"
#include "../sdlutils/InputHandler.h"

void GameOverState::enter() {
    // Setup para GameOverState
    // Aquí podrías mostrar algún mensaje de Game Over
}

void GameOverState::exit() {
    // Limpieza para GameOverState si es necesario
}

void GameOverState::update() {
    // Si el usuario pulsa cualquier tecla, cambiamos al estado NewGameState
    if (ih().keyDownEvent()) {
        
    }
}
