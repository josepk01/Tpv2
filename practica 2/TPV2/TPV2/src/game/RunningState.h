#pragma once

#include "GameState.h"
#include "../ecs/Manager.h" // Asegúrate de que este include sea correcto según tu estructura de carpetas

class RunningState : public GameState {
public:
    RunningState();
    virtual ~RunningState();

    void enter() override;
    void exit() override;
    void update() override;

private:
    ecs::Manager* mngr_; // Asumiendo que todos los sistemas se gestionan a través de ecs::Manager
};
