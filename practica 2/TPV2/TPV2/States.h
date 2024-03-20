#pragma once
class GameState {
public:
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
};

class RunningState : public GameState {
    void enter() override {
        // Preparar juego para correr
    }
    void update() override {
        // Actualizar sistemas, chequear transiciones de estado
    }
    void exit() override {
        // Limpiar estado corriendo
    }
};