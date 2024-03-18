#pragma once
#include "../ecs/ecs.h"

using ecs::entity_t;

class MissilesFacade {
public:
    MissilesFacade() {}
    virtual ~MissilesFacade() {}
    virtual void remove_all_missiles() = 0;
    virtual void add_missile() = 0;
};