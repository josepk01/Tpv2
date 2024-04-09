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
    currentGhosts_ = 0;
}

void GhostSystem::blueColor() {
    auto mngr = Game::instance().getMngr();
    for (auto e : mngr->getEntities(ecs::grp::GHOSTS)) {
        ImageWithFrames* image = mngr->getComponent<ImageWithFrames>(e);
        std::cout << "blueColor!!";
        image->changeAnimation(6, 8);
    }
}

void GhostSystem::normalColor() {
    auto mngr = Game::instance().getMngr();
    for (auto e : mngr->getEntities(ecs::grp::GHOSTS)) {
        ImageWithFrames* image = mngr->getComponent<ImageWithFrames>(e);
        image->changeAnimation(4, 8);
    }
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

        int spawnSide = rand_.nextInt(0, 4); // 0: Arriba izquierda, 1: Arriba derecha, 2: Abajo derecha, 3: Abajo izquierda
        Vector2D p;
        switch (spawnSide) {
        case 0: // Arriba izquierda
            p = Vector2D(0, 0);
            break;
        case 1: // Arriba derecha
            p = Vector2D(width_ - 30, 0); // Asumiendo que el fantasma tiene un ancho de 30
            break;
        case 2: // Abajo derecha
            p = Vector2D(width_ - 30, height_ - 30); // Asumiendo que el fantasma tiene un alto de 30
            break;
        case 3: // Abajo izquierda
            p = Vector2D(0, height_ - 30);
            break;
        default:
            p = Vector2D(width_ / 2, height_ / 2); // Por defecto, en caso de cualquier otro número, lo ponemos en el centro (no debería ocurrir)
            break;
        }

        Vector2D v = Vector2D(0.0f, 0.0f); // La velocidad inicial puede ser (0,0) si los fantasmas comienzan estáticos

        auto mngr = Game::instance().getMngr();
        auto a = mngr->addEntity(ecs::grp::GHOSTS);
        mngr->addComponent<Transform>(a, p, v, 30, 30, 0.0f); // Establece la posición 'p' calculada anteriormente

        Texture* texture = &sdlutils().images().at("pacman_sprites");
        mngr->addComponent<ImageWithFrames>(a,
            texture,
            8, 8, 0, 4,
            1028 / 8, 1028 / 8,
            0, 0, 1, 4)->changeAnimation(4, 8);

        auto pacman = mngr->getHandler(ecs::hdlr::PACMAN);
        auto pacmanTR = mngr->getComponent<Transform>(pacman);
        mngr->addComponent<RandomFollow>(a, pacmanTR->getPos());
    }
}
