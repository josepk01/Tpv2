#pragma once
#include "GameState.h"
#include <SDL_rect.h>
#include "../sdlutils/Texture.h"


class NewGameState : public GameState {
public:
    NewGameState();
    virtual ~NewGameState(); 
    void enter() override;
    void exit() override;
    void update() override;
private:
    Texture* newGameText_;

};
