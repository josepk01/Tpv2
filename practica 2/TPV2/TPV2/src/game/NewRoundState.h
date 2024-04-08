
#pragma once
#include "GameState.h"

class NewRoundState : public GameState {
public:
    NewRoundState(); // Constructor sin argumentos
    virtual ~NewRoundState();

    void enter() override;
    void exit() override;
    void update() override;
};
