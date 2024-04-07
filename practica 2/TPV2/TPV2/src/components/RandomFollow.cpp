#include "RandomFollow.h"

#include <cmath>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

RandomFollow::RandomFollow(Vector2D& to_follow) :
    to_follow_(to_follow), //
    tr_(nullptr), //
    rand_(sdlutils().rand()) {
}

RandomFollow::~RandomFollow() {
}

void RandomFollow::initComponent() {
    tr_ = mngr_->getComponent<Transform>(ent_);
    assert(tr_ != nullptr);
}

void RandomFollow::update() {

    std::cout << "RANDOMMMM";
    auto& pos = tr_->getPos();
    auto& vel = tr_->getVel();

    // Obtiene la posición actual del caza para seguir
    Vector2D targetPos = to_follow_;

    // Actualizamos la direccion de la velocidad si se da la probabilidad
    auto g = rand_.nextInt(0, 500);

    if (g == 0) {
        // Calcula el vector de dirección hacia el caza
        Vector2D dir = (targetPos - pos).normalize();
        // Cambia la velocidad
        vel = dir * vel.magnitude();
        tr_->vel_ = vel;
    }
}

