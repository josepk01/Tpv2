#pragma once

#include "Game.h"
#include "../ecs/Manager.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems//FruitSystem.h"

class GameState {
public:
    GameState(ecs::Manager* mngr) : mngr_(mngr) {}

    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
protected:
    ecs::Manager* mngr_;
    FruitSystem* foodSys_;
    ecs::System* pacmanSys_;
    ecs::System* gameCtrlSys_;
    ecs::System* startsSys_;
    ecs::System* renderSys_;
    ecs::System* collisionSys_;
    ecs::System* ghostSys_;
};

// Estado para crear un nuevo juego
class CreateNewGameState : public GameState {
public:
    void enter() override {
        // Lógica para crear un nuevo juego
    }

    void update() override {
        // Lógica de actualización, si es necesaria
    }

    void exit() override {
        // Lógica de limpieza al salir del estado de creación de juego
    }
};

// Estado para comenzar una ronda
class StartRoundState : public GameState {
public:
    void enter() override {
        // Lógica para comenzar una ronda
    }

    void update() override {
        // Lógica de actualización, si es necesaria
    }

    void exit() override {
        // Lógica de limpieza al salir del estado de inicio de ronda
    }
};

// Estado de juego en ejecución
class RunningState : public GameState {
public:
    RunningState(ecs::Manager* mngr) : GameState(mngr) {}

    void enter() override {
        // add the systems
        pacmanSys_ = mngr_->addSystem<PacManSystem>();
        foodSys_ = mngr_->addSystem<FruitSystem>();
        gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
        renderSys_ = mngr_->addSystem<RenderSystem>();
        ghostSys_ = mngr_->addSystem<GhostSystem>();
        collisionSys_ = mngr_->addSystem<CollisionsSystem>();
    }

    void update() override {
        if (mngr_ != nullptr) {
            std::cout << "MANAGER ESTAAA";
            mngr_->refresh();
            renderSys_->update();
            pacmanSys_->update();
            foodSys_->update();
            gameCtrlSys_->update();
            ghostSys_->update();
            collisionSys_->update();
        }
    }

    void exit() override {
        // Limpiar estado de ejecución del juego
    }
};

// Estado de pausa
class PauseState : public GameState {
public:
    void enter() override {
        // Lógica para pausar el juego
    }

    void update() override {
        // Lógica de actualización, si es necesaria
    }

    void exit() override {
        // Lógica para salir del estado de pausa
    }
};

// Estado de juego terminado
class GameOverState : public GameState {
public:
    void enter() override {
        // Lógica para manejar el estado de juego terminado
    }

    void update() override {
        // Lógica de actualización, si es necesaria
    }

    void exit() override {
        // Lógica para salir del estado de juego terminado
    }
};