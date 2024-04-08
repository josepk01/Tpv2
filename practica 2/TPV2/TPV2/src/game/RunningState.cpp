#include "RunningState.h"
#include "Game.h"

RunningState::RunningState() {
    // Aquí podrías inicializar recursos si es necesario
    ;
}

RunningState::~RunningState() {
    // Aquí limpias los recursos si es necesario
    ;
}

void RunningState::enter() {
    // Inicialización específica del estado Running
    // Si necesitas acceso al Manager puedes obtenerlo desde Game::instance()->getMngr()
    ;
}

void RunningState::exit() {
    // Limpieza específica del estado Running
    ;
}

void RunningState::update() {
    //auto mngr = instance->getMngr();
    ;
    //// Ahora puedes llamar a update en todos los sistemas a través del manager
    //// Esto asume que el manager tiene una manera de iterar sobre todos los sistemas y llamar a update, o una forma de obtener cada sistema individualmente.
    //mngr->update();
}