#pragma once
#include "GameState.h"
#include "../sdlutils/Texture.h"
class PauseState : public GameState {
public:
    PauseState();
    ~PauseState() override;
    void enter() override;
    void update() override;
    void exit();
private:
    Texture* pauseText_;
};
