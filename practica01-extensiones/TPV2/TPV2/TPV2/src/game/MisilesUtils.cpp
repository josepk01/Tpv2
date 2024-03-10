// MisilesUtils.cpp
#include "MisilesUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Follow.h"
#include "Game.h"

MisilesUtils::MisilesUtils() :
    rand_(sdlutils().rand()), width_(sdlutils().width()), height_(sdlutils().height()) {
}

MisilesUtils::~MisilesUtils() {
}

void MisilesUtils::create_misil() {
    // Lógica para añadir un misil
    generateMisil();
}

void MisilesUtils::remove_all_misiles() {
    auto mngr = Game::instance()->getMngr();
    for (auto e : mngr->getEntities(ecs::grp::MISILES)) {
        mngr->setAlive(e, false);
    }
    mngr->refresh();
}

void MisilesUtils::generateMisil() {
    auto mngr = Game::instance()->getMngr();
    auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
    auto fighterTR = mngr->getComponent<Transform>(fighter);

    // Esquinas de la pantalla
    Vector2D corners[4] = {
        Vector2D(0, 0), // Esquina superior izquierda
        Vector2D(sdlutils().width(), 0), // Esquina superior derecha
        Vector2D(0, sdlutils().height()), // Esquina inferior izquierda
        Vector2D(sdlutils().width(), sdlutils().height()) // Esquina inferior derecha
    };

    // Seleccionar una esquina aleatoriamente
    Vector2D startPosition = corners[rand_.nextInt(0, 4)];

    // Calcular vector de velocidad hacia el caza
    Vector2D direction = (fighterTR->getPos() - startPosition).normalize();
    float speedMagnitude = rand_.nextInt(1, 4); // Velocidad entre 1 y 3
    Vector2D velocity = direction * speedMagnitude;

    // Crear la entidad misil y añadirle componentes
    auto misil = mngr->addEntity(ecs::grp::MISILES);
    mngr->addComponent<Transform>(misil, startPosition, velocity, 10, 10, 0.0f);
    mngr->addComponent<Image>(misil, &sdlutils().images().at("missile"));
    auto misilTR = mngr->getComponent<Transform>(misil);
    mngr->addComponent<Follow>(misil, fighterTR->getPos());

    // Ajustar la rotación inicial del misil para que apunte hacia el caza
    Vector2D reference(0, -1); // Vector de referencia para calcular la rotación
    float angle = reference.angle(velocity);
    misilTR->setRot(angle);
}

