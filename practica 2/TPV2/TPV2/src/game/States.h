#pragma once

#include "Game.h"
#include "../ecs/Manager.h"

class GameState {
public:
    GameState(ecs::Manager* mngr) : mngr_(mngr) {}

    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
protected:
    ecs::Manager* mngr_;
};

// Estado para crear un nuevo juego
class CreateNewGameState : public GameState {
public:
    void enter() override {
        // L�gica para crear un nuevo juego
    }

    void update() override {
        // L�gica de actualizaci�n, si es necesaria
    }

    void exit() override {
        // L�gica de limpieza al salir del estado de creaci�n de juego
    }
};

// Estado para comenzar una ronda
class StartRoundState : public GameState {
public:
    void enter() override {
        // L�gica para comenzar una ronda
    }

    void update() override {
        // L�gica de actualizaci�n, si es necesaria
    }

    void exit() override {
        // L�gica de limpieza al salir del estado de inicio de ronda
    }
};

// Estado de juego en ejecuci�n
class RunningState : public GameState {
public:
    RunningState(ecs::Manager* mngr) : GameState(mngr) {}

    void enter() override {
        // Preparar el juego para correr
    }

    void update() override {
        if (mngr_ != nullptr) {
            std::cout << "MANAGER ESTAAA";
            mngr_->refresh();
        }
    }

    void exit() override {
        // Limpiar estado de ejecuci�n del juego
    }
};

// Estado de pausa
class PauseState : public GameState {
public:
    void enter() override {
        // L�gica para pausar el juego
    }

    void update() override {
        // L�gica de actualizaci�n, si es necesaria
    }

    void exit() override {
        // L�gica para salir del estado de pausa
    }
};

// Estado de juego terminado
class GameOverState : public GameState {
public:
    void enter() override {
        // L�gica para manejar el estado de juego terminado
    }

    void update() override {
        // L�gica de actualizaci�n, si es necesaria
    }

    void exit() override {
        // L�gica para salir del estado de juego terminado
    }
};