#pragma once

#include "../ecs/System.h"
#include "../utils/Vector2D.h"
#include <vector>

class FoodSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::FRUITS)
    FoodSystem();
    virtual ~FoodSystem();

    void initSystem() override;
    void update() override;

private:
    std::vector<ecs::Entity*> fruits;
    void generateFruits();

};