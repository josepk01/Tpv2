#include "NewRoundState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"


NewRoundState::NewRoundState() : newRoundText_(nullptr) {}

NewRoundState::~NewRoundState() {
    if (newRoundText_ != nullptr) {
        delete newRoundText_;
        newRoundText_ = nullptr;
    }
}

void NewRoundState::enter() {
    SDL_Color color = { 255, 255, 255, 255 }; // Color blanco
    newRoundText_ = new Texture(sdlutils().renderer(), "Partida Nueva",
        sdlutils().fonts().at("ARIAL24"), color);

    sdlutils().clearRenderer();
    if (newRoundText_ != nullptr) {
        newRoundText_->render((sdlutils().width() - newRoundText_->width()) / 2,
            (sdlutils().height() - newRoundText_->height()) / 2);
    }
    sdlutils().presentRenderer();

}

void NewRoundState::update() {
    if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_RETURN)) {
        Game::instance().setState(Game::RUNNING);
    }
}

void NewRoundState::exit() {
    delete newRoundText_;
    newRoundText_ = nullptr;
}
