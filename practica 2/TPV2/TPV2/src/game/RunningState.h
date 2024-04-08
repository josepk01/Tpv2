#pragma once

#include "GameState.h"
#include "../ecs/Manager.h" // Aseg�rate de que este include sea correcto seg�n tu estructura de carpetas

class RunningState : public GameState {
public:
    RunningState();
    virtual ~RunningState();

    void enter() override;
    void exit() override;
    void update() override;

private:
    ecs::Manager* mngr_; // Asumiendo que todos los sistemas se gestionan a trav�s de ecs::Manager
};
