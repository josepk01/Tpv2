#include "CollisionsSystem.h"
#include "../components/Transform.h"
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
    Message msg;
    msg.id = _m_PACMAN_FOOD_COLLISION;
    // Asumiendo que necesitas el identificador de la entidad y el sistema lo proporciona
    // De lo contrario, ajusta según tu sistema de ECS.
    msg.star_eaten_data.e = fruit; // Si msg.star_eaten_data.e es un ecs::Entity*
    mngr_->send(msg);

    mngr_->setAlive(fruit, false);
}

void CollisionsSystem::handleGhostCollision(ecs::Entity* pacman, ecs::Entity* ghost) {
    Message msg;
    msg.id = _m_PACMAN_GHOST_COLLISION;
    msg.star_eaten_data.e = ghost; // Ajusta según tu sistema de ECS.
    mngr_->send(msg);

    mngr_->setAlive(ghost, false);
}
