
#pragma once
#include "GameState.h"
#include "../sdlutils/Texture.h"
#include "../ecs/System.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/GhostSystem.h"
#include "../ecs/Manager.h" 
class NewRoundState : public GameState {
public:
    NewRoundState(); // Constructor sin argumentos
    virtual ~NewRoundState();

    void enter() override;
    void exit() override;
    void update() override;
private:
    ecs::Manager* mngr_;
    GhostSystem* ghostSys_;
    Texture* newRoundText_;
};
