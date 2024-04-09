#include "PauseState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PauseState::PauseState() : pauseText_(nullptr) {}

PauseState::~PauseState() {
    if (pauseText_ != nullptr) {
        delete pauseText_;
        pauseText_ = nullptr;
    }
}

void PauseState::enter() {
    SDL_Color color = { 255, 255, 255, 255 }; // Color blanco
    pauseText_ = new Texture(sdlutils().renderer(), "En Pausa",
        sdlutils().fonts().at("ARIAL24"), color);

    sdlutils().clearRenderer();
    // Mostrar el mensaje "En Pausa" en el centro de la pantalla
    if (pauseText_ != nullptr) {
        pauseText_->render((sdlutils().width() - pauseText_->width()) / 2,
            (sdlutils().height() - pauseText_->height()) / 2);
    }

    sdlutils().presentRenderer();

}

void PauseState::update() {
    if (ih().keyDownEvent() && (ih().isKeyDown(SDL_SCANCODE_RETURN)|| ih().isKeyDown(SDL_SCANCODE_P))) {
        Game::instance().setState(Game::RUNNING);
    }

}

void PauseState::exit() {
    sdlutils().virtualTimer().resume();
    // Si la textura se crea en enter() y se destruye aquí, asegúrate de liberarla
    delete pauseText_;
    pauseText_ = nullptr;
}
