#pragma once

#include "GameState.h"
#include "../ecs/Manager.h" 

class RunningState : public GameState {
public:
    RunningState();
    virtual ~RunningState();

    void enter() override;
    void exit() override;
    void update() override;

private:
    ecs::Manager* mngr_; 
};
