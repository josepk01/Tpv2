#pragma once
#include "../ecs/ecs.h"

using ecs::entity_t;

class MisilesFacade {
public:
    MisilesFacade();
    virtual ~MisilesFacade();
    virtual void create_misil() = 0;
    virtual void remove_all_misiles() = 0;
};
