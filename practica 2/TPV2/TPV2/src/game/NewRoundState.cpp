#include "NewRoundState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

NewRoundState::NewRoundState() : ih(ih()) {}

NewRoundState::~NewRoundState() {}

void NewRoundState::enter() {
    // Configuraci�n espec�fica para el inicio de una nueva ronda
}

void NewRoundState::leave() {
    // Limpieza espec�fica al salir del estado de nueva ronda
}

void NewRoundState::update() {
    if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_RETURN)) {
        Game::instance().setState(Game::State::RUNNING); // Asume que Game::State es un enum con los estados posibles
    }
    // No es necesario llamar a render aqu� si solo se va a cambiar el estado
}