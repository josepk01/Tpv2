#pragma once
#include "GameState.h"
#include <SDL_rect.h>
class NewGameState : public GameState {
public:
    void enter() override;
    void exit() override;
    void update() override;
};
