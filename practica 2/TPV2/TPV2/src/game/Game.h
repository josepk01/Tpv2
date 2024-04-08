// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "../ecs/ecs.h"
#include "../../States.h"
#include "../systems/FruitSystem.h"
class Game {
public:
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
    GameState* currentState_;
};
