// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"

PacManSystem::PacManSystem() :
		pmTR_(nullptr), 
		lives_(3) {
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
	// Inicializar componente de animación con la primera animación (normal)
	Texture* pacmanTexture = &sdlutils().images().at("pacman_sprites");
	pmImage_ = mngr_->addComponent<ImageWithFrames>(pacman,
		pacmanTexture,
		8, // Número total de columnas en la hoja de sprites.
		8, // Número total de filas en la hoja de sprites.
		0, // X inicial de la animación en la textura (fila de animación normal).
		0, // Y inicial de la animación en la textura (columna de animación normal).
		frameWidth, // Ancho de cada frame.
		frameHeight, // Alto de cada frame.
		0, // Columna inicial para la animación normal.
		0, // Fila inicial para la animación normal.
		1, // Número de columnas (frames) para la animación normal.
		4  // Número de filas para la animación normal.
	);
	pmState_ = PacManState::NORMAL; // Estado inicial de Pac-Man.
}

void PacManSystem::update() {

	std::cout << isImmortal;

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			pmTR_->rot_ = 90.0f;
			pmTR_->vel_ = Vector2D(SPEED * 0.1, 0);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			pmTR_->rot_ = -90.0f;
			pmTR_->vel_ = Vector2D(-SPEED * 0.1, 0);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed
			pmTR_->rot_ = 0.0f;
			pmTR_->vel_ = Vector2D(0, -SPEED * 0.1);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
			pmTR_->rot_ = 180.0f;
			pmTR_->vel_ = Vector2D(0, SPEED * 0.1);
		}

	}

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
	// Cambiar el estado de animación en función de la lógica del juego
	switch (pmState_) {
	case PacManState::NORMAL:
		if (pmlState_ != pmState_)
		changePacManState(PacManState::NORMAL);
		break;
	case PacManState::IMMORTAL:
		if (pmlState_ != pmState_)
		changePacManState(PacManState::IMMORTAL);
		break;
	case PacManState::DEAD:
		if (pmlState_ != pmState_)
		changePacManState(PacManState::DEAD);
		break;
	}
	checkImmortalState();
}

bool PacManSystem::isInmortal()
{
	return pmState_ == PacManState::IMMORTAL;
}

void PacManSystem::changePacManState(PacManState newState) {
    // Asegurarse de cambiar la animación solo si el estado ha cambiado.
    if (pmState_ != newState) {
        pmState_ = newState;
        switch (pmState_) {
            case PacManState::NORMAL:
                // Supongamos que la animación normal está en la primera fila (fila 0).
                pmImage_->changeAnimation(0, 4); // Cambiar a la animación en la fila 0 con 4 frames.
                break;
            case PacManState::IMMORTAL:
                // La animación inmortal está en la tercera fila (fila 2).
                pmImage_->changeAnimation(2, 4); // Cambiar a la animación en la fila 2 con 4 frames.
                break;
            case PacManState::DEAD:
                // La animación de muerte está en la cuarta fila (fila 3).
                pmImage_->changeAnimation(3, 4); // Cambiar a la animación en la fila 3 con 4 frames.
                break;
            // Añadir más estados y animaciones según sea necesario.
        }
    }
}


void PacManSystem::startImmortalState() {
	changePacManState(PacManState::IMMORTAL);
	immortalStartTime_ = SDL_GetTicks();
	isImmortal = true;
}

void PacManSystem::checkImmortalState() {
	if (isImmortal && (SDL_GetTicks() - immortalStartTime_ >= 5000)) { // 5 segundos
		isImmortal = false;
		changePacManState(PacManState::NORMAL);
		Message m;
		m.id = _m_IMMUNITY_END;
		mngr_->send(m);
	}
}
// Método para perder una vida y reiniciar o terminar el juego
void PacManSystem::loseLife() {
	if (lives_ >= 0) {
		--lives_;
		// Si todavía quedan vidas, reinicia la posición de Pac-Man
		resetPacManPosition();

		if (lives_ == 0) {
			// Cambiar a estado muerto si no quedan vidas
			reset();
			changePacManState(PacManState::DEAD);
			// Aquí puedes agregar lógica para terminar el juego o reiniciarlo completamente
		}

	}
}

// Método para reiniciar la posición de Pac-Man y cambiarlo al estado normal
void PacManSystem::resetPacManPosition() {
	auto s = 50.0f;
	auto x = (sdlutils().width() + s) / 2.0f;
	auto y = (sdlutils().height() + s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	changePacManState(PacManState::NORMAL);
}