#pragma once
#include "GameState.h"

class NewGameState : public GameState {
public:
    void enter(Game* game) override;
    void exit(Game* game) override;
    void update(Game* game) override;
};
