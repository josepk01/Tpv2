#pragma once
#include "MisilesFacade.h"
#include "../components/Follow.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

class Vector2D;
class RandomNumberGenerator;

class MissilesUtils : public MissilesFacade {
public:
    MissilesUtils();
    virtual ~MissilesUtils();

    void remove_all_missiles() override;

    void add_missile() override;

private:
    void generateMissile();
    RandomNumberGenerator& rand_;
    int width_;
    int height_;
};
