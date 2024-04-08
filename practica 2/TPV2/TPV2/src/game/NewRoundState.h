#pragma once
#include "GameState.h"
#include <SDL_rect.h>

class NewRoundState : public GameState {
public:
    void NewRoundState();
    void enter() override;
    void exit() override;
    void update() override;
};
