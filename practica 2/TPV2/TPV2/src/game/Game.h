// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "../ecs/ecs.h"
#include "../../States.h"
#include "../systems/FruitSystem.h"
class Game {
public:
    enum State {
        RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
    };
    static Game& instance() {
        static Game instance; // Instancia única
        return instance;
    }
    inline ecs::Manager* getMngr() {
        return mngr_;
    }

    virtual ~Game();

    void init();
    void start();
    void changeState(GameState* newState);

    // Elimina la capacidad de copiar o asignar la instancia
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    inline void setState(State s) {
        GameState* new_state = nullptr;
        switch (s) {
        case RUNNING:
            new_state = runing_state_;
            break;
        case PAUSED:
            new_state = paused_state_;
            break;
        case NEWGAME:
            new_state = newgame_state_;
            break;
        case NEWROUND:
            new_state = newround_state_;
            break;
        case GAMEOVER:
            new_state = gameover_state_;
            break;
        default:
            break;
        }
        current_state_->exit();
        current_state_ = new_state;
        current_state_->enter();
    }

private:
    Game(); // Constructor privado
    FruitSystem* foodSys_;
    ecs::Manager* mngr_;
    ecs::System* pacmanSys_;
    ecs::System* gameCtrlSys_;
    ecs::System* startsSys_;
    ecs::System* renderSys_;
    ecs::System* collisionSys_;
    ecs::System* ghostSys_;

    GameState* current_state_;
    GameState* paused_state_;
    GameState* runing_state_;
    GameState* newgame_state_;
    GameState* newround_state_;
    GameState* gameover_state_;
};
