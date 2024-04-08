#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
class CollisionsSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::COLLISIONS)

        CollisionsSystem();
    virtual ~CollisionsSystem();

    void initSystem() override;
    void update() override;

    bool checkCollision(Transform* a, Transform* b);

private:
    void handleFruitCollision(ecs::Entity* pacman, ecs::Entity* fruit);
    void handleGhostCollision(ecs::Entity* pacman, ecs::Entity* ghost);
};
