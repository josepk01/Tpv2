// This file is part of the course TPV2@UCM - Samir Genaim

#include "Follow.h"

#include <cmath>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

Follow::Follow(Vector2D &to_follow) :
		to_follow_(to_follow), //
		tr_(nullptr) {

}

Follow::~Follow() {
}

void Follow::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Follow::update() {
    auto& pos = tr_->getPos();
    auto& vel = tr_->getVel();

    // Obtiene la posici�n actual del caza para seguir
    Vector2D targetPos = to_follow_;

    // Calcula el vector de direcci�n hacia el caza
    Vector2D dir = (targetPos - pos).normalize();

    // Actualiza la velocidad del misil hacia el caza
    // Aseg�rate de que la magnitud de la velocidad se mantiene
    vel = dir * vel.magnitude();

    // Actualiza la rotaci�n del misil para que apunte hacia el caza
    // Calcula el �ngulo entre el vector de direcci�n del misil (0, -1) como referencia y el vector de velocidad actual
    // Se asume que el misil "mira" hacia arriba con respecto a su sprite original
    float angle = Vector2D(0, -1).angle(vel);
    tr_->setRot(angle);
}

