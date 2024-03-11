#include "Rotate.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"

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
	//assert(tr_ != nullptr);
}

void Rotate::update() {
	tr_->setRot(tr_->getRot() + rotVel_);
}
