
#pragma once

class GameState {
public:
    virtual ~GameState() = default;
    virtual void enter() = 0;
    virtual void exit() = 0;
};
