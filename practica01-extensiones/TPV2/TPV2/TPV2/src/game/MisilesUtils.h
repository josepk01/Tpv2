#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "MisilesFacade.h"

class MisilesUtils : public MisilesFacade {
public:
    MisilesUtils();
    virtual ~MisilesUtils();
    void create_misil() override;
    void remove_all_misiles() override;

private:
    RandomNumberGenerator rand_;
    float width_, height_;
    void generateMisil();
};
