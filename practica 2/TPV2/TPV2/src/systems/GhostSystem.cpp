#include "GhostSystem.h"
#include "../components/Transform.h"
#include "../components/RandomFollow.h"
#include "../components/ImageWithFrames.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

GhostSystem::GhostSystem() : rand_(sdlutils().rand()), width_(sdlutils().width()), height_(sdlutils().height()) {

}
GhostSystem::~GhostSystem(){

}

void GhostSystem::remove_all_ghost() {
	auto mngr = Game::instance().getMngr();
	for (auto e : mngr->getEntities(ecs::grp::GHOSTS)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}

void GhostSystem::eateable_state() {

}

void GhostSystem::update() {
	if (timer_.currTime() > timeToSpawn_ * 1000) {
		generateGhost();
		timer_.reset();
	}
}

void GhostSystem::generateGhost() {

	if (currentGhosts_ < maxGhosts_) {
		currentGhosts_++;

		//std::cout << "ghost generar";

		int spawnSide = rand_.nextInt(0, 4);

		switch (spawnSide) {
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			break;
		}

		Vector2D p = Vector2D(width_/2, height_/2);

		Vector2D v = Vector2D(0.0f, 0.0f);

		auto g = rand_.nextInt(1, 4);

		auto mngr = Game::instance().getMngr();

		auto a = mngr->addEntity(ecs::grp::GHOSTS);

		mngr->addComponent<Transform>(a, p, p, 10 + 5 * g, 10 + 5 * g, 0.0f);

		Texture* Texture = &sdlutils().images().at("pacman_sprites");
		mngr->addComponent<ImageWithFrames>(a, //
			Texture, //
			8, // Número total de columnas en la hoja de sprites.
			8, // Número total de filas en la hoja de sprites.
			0, // X inicial de la animación en la textura (fila de animación normal).
			4, // Y inicial de la animación en la textura (columna de animación normal).
			1028 / 8, // Ancho de cada frame. Hay 8 columnas
			1028 / 8, // Alto de cada frame. Hay 8 columnas
			0, // Columna inicial para la animación normal.
			0, // Fila inicial para la animación normal.
			1, // Número de columnas (frames) para la animación normal.
			4  // Número de filas para la animación normal.
		);

		auto pacman = mngr->getHandler(ecs::hdlr::PACMAN);

		auto pacmanTR = mngr->getComponent<Transform>(pacman);

		mngr->addComponent<RandomFollow>(a, pacmanTR->getPos());
	}
}