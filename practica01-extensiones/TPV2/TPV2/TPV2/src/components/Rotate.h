#pragma once
#include "../ecs/Component.h"
class Transform;

class Vector2D;

class Rotate : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::ROTATE)

	Rotate(float rotVel);
	virtual ~Rotate();
	void initComponent() override;
	void update() override;

private:
	float rotVel_;
	Transform* tr_;
};


