#include "GameOverState.h"
#include "Game.h"
#include "NewGameState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

GameOverState::GameOverState() : gameOverText_(nullptr) {}

GameOverState::~GameOverState() {
    if (gameOverText_ != nullptr) {
        delete gameOverText_;
        gameOverText_ = nullptr;
    }
}

void GameOverState::enter() {
    SDL_Color color = { 255, 255, 255, 255 }; // Color blanco
    gameOverText_ = new Texture(sdlutils().renderer(), "Game Over",
        sdlutils().fonts().at("ARIAL24"), color);

    sdlutils().clearRenderer();
    // Asumiendo que ya has creado la textura "gameOverText_"
    if (gameOverText_ != nullptr) {
        gameOverText_->render((sdlutils().width() - gameOverText_->width()) / 2,
            (sdlutils().height() - gameOverText_->height()) / 2);
    }

    sdlutils().presentRenderer();

}

void GameOverState::exit() {
    // Si la textura se crea en enter() y se destruye en exit(), asegúrate de liberarla aquí
}

void GameOverState::update() {
    if (ih().keyDownEvent() && ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_RETURN)) {
        Game::instance().setState(Game::NEWGAME);
    }

}
