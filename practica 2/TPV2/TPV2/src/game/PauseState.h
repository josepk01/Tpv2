#pragma once
#include "GameState.h"

class PauseState : public GameState {
public:
    PauseState();
    ~PauseState() override;
    void enter() override;
    void update() override;
    void exit();
};
