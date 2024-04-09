#include "CollisionsSystem.h"
#include "../components/Transform.h"
#include "../components/FruitComponent.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "PacManSystem.h"
#include "GhostSystem.h"
#include "FruitSystem.h"

CollisionsSystem::CollisionsSystem() {
    // Constructor
}

CollisionsSystem::~CollisionsSystem() {
    // Destructor
}

void CollisionsSystem::initSystem() {
    // Inicialización necesaria
}

void CollisionsSystem::update() {
    auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
    auto pacmanTR = mngr_->getComponent<Transform>(pacman);

    // Comprobación de colisión con frutas
    for (auto& fruit : mngr_->getEntities(ecs::grp::FRUITS)) {
        auto fruitTR = mngr_->getComponent<Transform>(fruit);
        if (checkCollision(pacmanTR, fruitTR)) {
            handleFruitCollision(pacman, fruit);
        }
    }

    // Comprobación de colisión con fantasmas
    for (auto& ghost : mngr_->getEntities(ecs::grp::GHOSTS)) {
        auto ghostTR = mngr_->getComponent<Transform>(ghost);
        if (checkCollision(pacmanTR, ghostTR)) {
            handleGhostCollision(pacman, ghost);
        }
    }
}
bool CollisionsSystem::checkCollision(Transform* a, Transform* b) {
    // AABB collision detection
    bool collisionX = a->pos_.getX() + a->width_ >= b->pos_.getX() &&
        b->pos_.getX() + b->width_ >= a->pos_.getX();
    bool collisionY = a->pos_.getY() + a->height_ >= b->pos_.getY() &&
        b->pos_.getY() + b->height_ >= a->pos_.getY();
    return collisionX && collisionY;
}
void CollisionsSystem::handleFruitCollision(ecs::Entity* pacman, ecs::Entity* fruit) {
    auto fruitTypeComponent = mngr_->getComponent<FruitComponent>(fruit);

    Message m;

    if (fruitTypeComponent->getMilagrosa()) {
        // Hacer a Pac-Man inmortal y permitir que coma fantasmas
        m.id = _m_IMMUNITY_START;
    }
    else {
        // Aumentar la puntuación de Pac-Man
        m.id = _m_PACMAN_FOOD_COLLISION;
        m.star_eaten_data.e = fruit;
    }
    mngr_->send(m);
    mngr_->setAlive(fruit, false);
}



void CollisionsSystem::handleGhostCollision(ecs::Entity* pacman, ecs::Entity* ghost) {
    auto pacmanSystem = mngr_->getSystem<PacManSystem>();

    if (!pacmanSystem->isInmortal()) {
        // Pac-Man come al fantasma y aumenta su puntuación
        Message m;
        m.id = _m_PACMAN_GHOST_COLLISION;
        m.star_eaten_data.e = ghost;
        mngr_->send(m);
    }
    if(pacmanSystem->getlives()<=0){
        // Pac-Man muere
        pacmanSystem->changePacManState(PacManState::DEAD);
        // Podrías querer enviar un mensaje específico aquí también
    }

    mngr_->setAlive(ghost, false);
}


