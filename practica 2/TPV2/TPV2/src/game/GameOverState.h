#pragma once
#include "GameState.h"
#include "../sdlutils/Texture.h"

class GameOverState : public GameState {
public:
    GameOverState();
    virtual ~GameOverState(); // Aseg�rate de liberar recursos de la textura aqu� si es necesario

    void enter() override;
    void exit() override;
    void update() override;

private:
    Texture* gameOverText_; // Puntero a la textura del mensaje "Game Over"
};
