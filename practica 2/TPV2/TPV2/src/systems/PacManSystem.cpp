// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"

PacManSystem::PacManSystem() :
		pmTR_(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	std::cout << "CREAR PACMAN";
	// create the PacMan entity
	//
	auto pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() + s) / 2.0f;
	auto y = (sdlutils().height() + s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));
	Texture* pacmanTexture = &sdlutils().images().at("pacman_sprites");
	auto pacmanNormal = mngr_->addEntity();

	int frameSize = 32; // Asume que cada frame es de 32x32 píxeles
	mngr_->addComponent<ImageWithFrames>(
		pacmanNormal,
		pacmanTexture,
		4, 1, // número de columnas y filas en la animación
		0, 0, // x e y inicial en la imagen
		frameSize, frameSize, // ancho y alto del frame
		0, 0, // columna y fila inicial del frame de inicio
		4, 1 // número total de columnas y filas
	);


}

void PacManSystem::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			pmTR_->rot_ = 90.0f;
			pmTR_->vel_ = Vector2D(SPEED, 0);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			pmTR_->rot_ = -90.0f;
			pmTR_->vel_ = Vector2D(-SPEED, 0);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed
			pmTR_->rot_ = 0.0f;
			pmTR_->vel_ = Vector2D(0, -SPEED);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
			pmTR_->rot_ = 180.0f;
			pmTR_->vel_ = Vector2D(0, SPEED);
		}

	}

	// move the pacman
	pmTR_->pos_ = pmTR_->pos_ + pmTR_->vel_;

	// check left/right borders
	if (pmTR_->pos_.getX() < 0) {
		pmTR_->pos_.setX(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getX() + pmTR_->width_ > sdlutils().width()) {
		pmTR_->pos_.setX(sdlutils().width() - pmTR_->width_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pmTR_->pos_.getY() < 0) {
		pmTR_->pos_.setY(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getY() + pmTR_->height_ > sdlutils().height()) {
		pmTR_->pos_.setY(sdlutils().height() - pmTR_->height_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

}
