#include "NewGameState.h"
#include "Game.h"
#include "NewRoundState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"


NewGameState::NewGameState() : newGameText_(nullptr) {}

NewGameState::~NewGameState() {
    if (newGameText_ != nullptr) {
        delete newGameText_;
        newGameText_ = nullptr;
    }
}

void NewGameState::enter() {
    SDL_Color color = { 255, 255, 255, 255 }; // Color blanco
    newGameText_ = new Texture(sdlutils().renderer(), "Juego Nuevo",
        sdlutils().fonts().at("ARIAL24"), color);

    sdlutils().clearRenderer();
    if (newGameText_ != nullptr) {
        newGameText_->render((sdlutils().width() - newGameText_->width()) / 2,
            (sdlutils().height() - newGameText_->height()) / 2);
    }
    sdlutils().presentRenderer();
}

void NewGameState::update() {
    if (ih().keyDownEvent()) {

        Game::instance().setState(Game::NEWROUND);
    }
}

void NewGameState::exit() {
    delete newGameText_;
    newGameText_ = nullptr;
}
