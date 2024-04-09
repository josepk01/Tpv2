#pragma once

#include "GameState.h"
#include "../ecs/Manager.h" 
#include "../sdlutils/InputHandler.h"
#include "../systems/GhostSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/FruitSystem.h"

class RunningState : public GameState {
public:
    RunningState();
    virtual ~RunningState();

    void enter() override;
    void exit() override;
    void update() override;

private:
    int currentl;
    ecs::Manager* mngr_; 


    GameCtrlSystem* gameCtrlSys_;

    PacManSystem* pacmanSys_;
    GhostSystem* ghostSys_;
    FruitSystem* foodSys_;

    RenderSystem* render_system;
    CollisionsSystem* collisionSys_;    
};
