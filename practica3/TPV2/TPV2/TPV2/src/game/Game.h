// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include <vector>

#include "../utils/Singleton.h"

class LittleWolf;
class Networking;

class Game : public Singleton<Game> {
    friend Singleton<Game>;
public:
    Game();
    virtual ~Game();
    bool init(char* host, Uint16 port);
    //void init();
    void start();

    LittleWolf& get_littlewolf() {
        return *little_wolf_;
    }
    Networking& getnetworking() {
        return *net_;
    }
private:
    LittleWolf *little_wolf_;
    Networking *net_;
};