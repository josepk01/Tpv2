#pragma once
#include "../ecs/Component.h"
class Transform;

class Vector2D;

class RandomNumberGenerator;

class RandomFollow : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::RANDOMFOLLOW)

	RandomFollow(Vector2D& to_follow);
	virtual ~RandomFollow();
	void initComponent() override;
	void update() override;

private:
	double followVelocity_ = 1;
	Vector2D& to_follow_;
	Transform* tr_;
	RandomNumberGenerator& rand_;
};

