#include "NewRoundState.h"



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

    auto mngr = Game::instance().getMngr();
    ghostSys_ = mngr->getSystem<GhostSystem>();
    if (ghostSys_) {
        ghostSys_->remove_all_ghost();
    }


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
