#pragma once
#include "../ecs/ecs.h"

using ecs::entity_t;

class BlackHoleFacade {
public:
	BlackHoleFacade() {
	}
	virtual ~BlackHoleFacade() {
	}
	virtual void create_black_holes(int n) = 0;
	virtual void remove_all_black_holes() = 0;
};


