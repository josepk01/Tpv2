#include "Rotate.h"

#include <cmath>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

Rotate::Rotate(float rotVel) :
	rotVel_(rotVel), //
	tr_(nullptr) {

}

Rotate::~Rotate() {
}

void Rotate::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Rotate::update() {
	auto& vel = tr_->getVel();
	vel = vel + Vector2D(0, -1).rotate(tr_->getRot()) * rotVel_;
}
