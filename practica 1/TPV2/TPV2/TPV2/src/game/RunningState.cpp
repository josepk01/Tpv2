// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "AsteroidsFacade.h"
#include "BlackHoleFacade.h"
#include "FighterFacade.h"
#include "MisilesFacade.h"

#include "Game.h"


RunningState::RunningState(AsteroidsFacade *ast_mngr, BlackHoleFacade *holes_mngr,FighterFacade *fighter_mngr, MissilesFacade *misile_mngr) :
		ihdlr(ih()), //
		ast_mngr_(ast_mngr), //
		holes_mngr(holes_mngr), //
		fighter_mngr_(fighter_mngr), //
		misile_mngr_(misile_mngr),
		lastTimeGeneratedAsteroids_(),
		lastTimeGeneratedMissiles_(sdlutils().virtualTimer().currTime()),
		missileGenerationInterval_(15000) {
}


RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {

	auto mngr = Game::instance()->getMngr();
	auto currentTime = sdlutils().virtualTimer().currTime();

	// check if fighter won
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		Game::instance()->setState(Game::GAMEOVER);
		return;
	}

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
		return;
	}
	// Verificar si es tiempo de generar un nuevo misil
	if (currentTime - lastTimeGeneratedMissiles_ >= missileGenerationInterval_) {
		misile_mngr_->add_missile(); // Asegúrate de que esta función existe y está implementada correctamente
		lastTimeGeneratedMissiles_ = currentTime;
	}

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto& misile = mngr->getEntities(ecs::grp::MISILES);
	auto &blackHoles = mngr->getEntities(ecs::grp::BLACKHOLES);

	// update
	mngr->update(fighter);
	for (auto a : asteroids) {
		mngr->update(a);
	}

	for (auto a : misile) {
		mngr->update(a);
	}
	for (auto a : blackHoles) {
		mngr->update(a);
	}

	// check collisions
	checkCollisions();

	// render
	sdlutils().clearRenderer();
	for (auto a : asteroids) {
		mngr->render(a);
	}

	for (auto a : misile) {
		mngr->render(a);
	}
	for (auto a : blackHoles) {
		mngr->render(a);
	}

	mngr->render(fighter);
	sdlutils().presentRenderer();

	mngr->refresh();

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedAsteroids_ + 5000) {
		ast_mngr_->create_asteroids(1);
		lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	}

}

void RunningState::enter() {
	lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
}

void RunningState::checkCollisions() {
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto &misile = mngr->getEntities(ecs::grp::MISILES);
	auto &blackHoles = mngr->getEntities(ecs::grp::BLACKHOLES);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	auto fighterGUN = mngr->getComponent<Gun>(fighter);

	auto num_of_asteroids = asteroids.size();
	for (auto i = 0u; i < num_of_asteroids; i++) {
		auto a = asteroids[i];
		if (!mngr->isAlive(a))
			continue;

		// asteroid with fighter
		auto aTR = mngr->getComponent<Transform>(a);
		if (Collisions::collidesWithRotation( //
				fighterTR->getPos(), //
				fighterTR->getWidth(), //
				fighterTR->getHeight(), //
				fighterTR->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
			onFigherDeath();
			return;
		}

		// asteroid with bullets
		for (Gun::Bullet &b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
						b.pos, //
						b.width, //
						b.height, //
						b.rot, //
						aTR->getPos(), //
						aTR->getWidth(), //
						aTR->getHeight(), //
						aTR->getRot())) {
					ast_mngr_->split_astroid(a);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}

		//asteroid with black-holes
		for (auto i = 0u; i < blackHoles.size(); i++) {
			auto b = blackHoles[i];
			auto bTR = mngr->getComponent<Transform>(b);
			if (Collisions::collidesWithRotation( //
				bTR->getPos(), //
				bTR->getWidth(), //
				bTR->getHeight(), //
				bTR->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
				ast_mngr_->teleport_asteroid(a);
				continue;
			}
		}
	}
	for (auto m : misile) {
		if (!mngr->isAlive(m)) continue;
		auto mTR = mngr->getComponent<Transform>(m);

		// Misil con caza
		if (Collisions::collidesWithRotation(
			mTR->getPos(), mTR->getWidth(), mTR->getHeight(), mTR->getRot(),
			fighterTR->getPos(), fighterTR->getWidth(), fighterTR->getHeight(), fighterTR->getRot())) {
			onFigherDeath();
			mngr->setAlive(m, false); // Eliminar misil
			return;
		}
	}
	for (Gun::Bullet& b : *fighterGUN) {
		if (b.used) {
			for (auto m : misile) {
				auto mTR = mngr->getComponent<Transform>(m);
				if (Collisions::collidesWithRotation(
					b.pos, b.width, b.height, b.rot,
					mTR->getPos(), mTR->getWidth(), mTR->getHeight(), mTR->getRot())) {
					// Bala y misil colisionan, ambos se eliminan
					mngr->setAlive(m, false);
					b.used = false;
				}
			}
		}
	}
	for (auto m : misile) {
		auto mTR = mngr->getComponent<Transform>(m);
		// Suponiendo que la ventana es width_ x height_
		if (mTR->getPos().getX() < 0 || mTR->getPos().getX() > sdlutils().width() ||
			mTR->getPos().getY() < 0 || mTR->getPos().getY() > sdlutils().height()) {
			mngr->setAlive(m, false); // Eliminar misil
		}
	}


	// black-holes with fighter
	for (auto i = 0u; i < blackHoles.size(); i++) {
		auto b = blackHoles[i];
		auto bTR = mngr->getComponent<Transform>(b);
		if (Collisions::collidesWithRotation( //
			bTR->getPos(), //
			bTR->getWidth(), //
			bTR->getHeight(), //
			bTR->getRot(), //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot())) {
			onFigherDeath();
			continue;
		}
	}
}

void RunningState::onFigherDeath() {
	sdlutils().soundEffects().at("explosion").play();
	if (fighter_mngr_->update_lives(-1) > 0)
		Game::instance()->setState(Game::NEWROUND);
	else
		Game::instance()->setState(Game::GAMEOVER);
}
