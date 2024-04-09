// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../components/Points.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/GhostSystem.h"
#include "PacManSystem.h"

//#include "StarsSystem.h"
GameCtrlSystem::GameCtrlSystem() :
		score_() {

}

GameCtrlSystem::~GameCtrlSystem() {
	// TODO Auto-generated destructor stub
}

void GameCtrlSystem::initSystem() {
}

void GameCtrlSystem::update() {
	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_SPACE)) {

			Message m;
			m.id = _m_PACMAN_CREATE_FOOD;
			m.create_stars_data.n = 5;
			mngr_->send(m);
		}
	}
}

void GameCtrlSystem::recieve(const Message& m) {
    auto pacManSystem = mngr_->getSystem<PacManSystem>();
    auto ghostSystem = mngr_->getSystem<GhostSystem>();
    switch (m.id) {
    case _m_PACMAN_FOOD_COLLISION:
        incrScore(10);
        break;
    case _m_PACMAN_GHOST_COLLISION:
        pacManSystem->loseLife();

        break;
    case _m_IMMUNITY_START:
        ghostSystem->blueColor();
        pacManSystem->startImmortalState();
        break;
    case _m_IMMUNITY_END:
        std::cout << "YA NO ES INMORTAL!";
        ghostSystem->normalColor();
        break;
    default:
        break;
    }
}

